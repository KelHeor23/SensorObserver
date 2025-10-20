#include "SaveToCSV.h"

#include <QDateTime>
#include <QDir>

#include "Data/Frames/Containers/EngineSensors/EngineSensors.h"
#include "Data/Frames/Containers/EscSensors/EscStatus1.h"
#include "Data/Frames/Containers/EscSensors/EscStatus2.h"
#include "Data/Frames/Containers/EscSensors/EscStatus3.h"
#include "Data/Frames/Containers/VoltageRegulators/VoltageRegulators.h"
#include "qlocale.h"
#include <iomanip>

UnifiedCsvWriter::UnifiedCsvWriter(uint64_t flush_interval_ms)
    : m_flush_interval(flush_interval_ms),
    m_running(true), m_thread(&UnifiedCsvWriter::run, this) {

    QDateTime now = QDateTime::currentDateTime();
    QString dateString = now.date().toString("dd_MM_yy");
    QString timeString = now.time().toString("hh_mm");

    QDir dir;
    if (!dir.exists("log")) {
        dir.mkdir("log");
    }

    QString dateDirPath = QString("log/%1").arg(dateString);
    if (!dir.exists(dateDirPath)) {
        dir.mkdir(dateDirPath);
    }

    QString fileName = QString("%1t%2.csv").arg(dateString, timeString);
    QString filePath = dateDirPath + "/" + fileName;

    m_filename = filePath.toStdString();
    // Запись заголовка CSV
    std::ofstream file(m_filename, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        file << buildCSVheader({{"time", "device_id", "isCustom"}
                                , EngineSensors::sensorNames, VoltageRegulators::sensorNames
                                , EscSensors::sensorNamesFrame1, EscSensors::sensorNamesFrame2
                                , EscSensors::sensorNamesFrame3, {"\n"}});
    }
}

UnifiedCsvWriter::~UnifiedCsvWriter() {
    stop();
}

void UnifiedCsvWriter::addEngineData(std::shared_ptr<EngineSensorsData> data) {
    const uint8_t device_id = data->canID & 0x07;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceDataCustom[device_id].engine = data;
    m_deviceDataCustom[device_id].escF1->speed = data->speed;
    m_deviceDataCustom[device_id].escF3->motor_temp = data->temperature;
    m_deviceDataCustom[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addRegulatorData(std::shared_ptr<VoltageRegulatorsData> data) {
    const uint8_t device_id = data->canID & 0x07;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceDataCustom[device_id].regulator = data;
    m_deviceDataCustom[device_id].escF1->comm_pwm = data->controlPWM;
    m_deviceDataCustom[device_id].escF2->voltage = data->inputVoltageHP | (data->inputVoltageLP & 0xF);
    m_deviceDataCustom[device_id].escF2->current = data->electricCurrent;
    m_deviceDataCustom[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addOtherSensorsData(std::shared_ptr<OtherSensorsData> data)
{
    const uint8_t device_id = data->canID & 0x07;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceDataCustom[device_id].other = data;
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addEscF1Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo1> data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceDataESC[device_id].escF1 = data;
    m_deviceDataESC[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addEscF2Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo2> data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceDataESC[device_id].escF2 = data;
    m_deviceDataESC[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addEscF3Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo3> data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceDataESC[device_id].escF3 = data;
    m_deviceDataESC[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::stop() {
    if (m_running) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_running = false;
            m_updated = true;
        }
        m_cv.notify_all();
        if (m_thread.joinable()) {
            m_thread.join();
        }
        flushAllData(); // Запись оставшихся данных
    }
}

std::string UnifiedCsvWriter::buildCSVheader(const std::vector<std::vector<std::string> > &vectors) {
    std::string result;
    bool first = true;
    for (const auto& vec : vectors) {
        for (const auto& elem : vec) {
            if (!first) {
                result += ",";
            }
            result += elem;
            first = false;
        }
    }
    return result;
}

std::string UnifiedCsvWriter::formatTimeWithMilliseconds(long long ms_since_epoch) {
    std::time_t seconds = ms_since_epoch / 1000;
    int milliseconds = ms_since_epoch % 1000;

    // Преобразуем в локальное время
    std::tm tm = *std::localtime(&seconds);

    // Формируем строку с датой и временем
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    // Добавляем миллисекунды с ведущими нулями
    oss << '.' << std::setw(3) << std::setfill('0') << milliseconds;

    return oss.str();
}

void UnifiedCsvWriter::run() {
    while (m_running) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, std::chrono::milliseconds(m_flush_interval), [this] {
            return m_updated || !m_running;
        });

        if (m_updated) {
            flushAllData();
            m_updated = false;
        }
    }
}

void UnifiedCsvWriter::flushAllData() {
    std::ofstream file(m_filename, std::ios::app);
    if (!file.is_open()) return;

    const uint64_t current_time = getCurrentTimeMillis();
    for (auto& [device_id, data] : m_deviceDataESC) {
        // Пропуск устаревших или неполных данных
        if (current_time - data.last_update > m_flush_interval * 5) continue;

        writeDeviceData(file, device_id, data, false);
    }
    for (auto& [device_id, data] : m_deviceDataCustom) {
        // Пропуск устаревших или неполных данных
        if (current_time - data.last_update > m_flush_interval * 5) continue;

        writeDeviceData(file, device_id, data, true);
    }
    file.flush();
}

void UnifiedCsvWriter::writeDeviceData(std::ofstream &file, uint8_t device_id, const DeviceData &data, bool isCustom) {
    //file << formatTimeWithMilliseconds(data.last_update)
    file << data.last_update
         << "," << static_cast<int>(device_id) << "," << (isCustom ? 1 : 0) << ",";

    if (isCustom) {
        data.escF1->recv_pwm = 0;
        data.escF2->bus_current = 0;

        data.escF3->cap_temp = 0;
        data.escF3->mcu_temp = 0;
    }

    file << std::fixed << std::setprecision(2);

    file << data.engine->runoutAngle << ","
         << data.engine->runoutAmplitude << ",";

    file << static_cast<int>(data.regulator->averageVoltageA) << ","
         << static_cast<int>(data.regulator->averageVoltageB) << ","
         << static_cast<int>(data.regulator->averageVoltageC) << ",";

    file << data.escF1->speed << ","
         << data.escF1->recv_pwm << ","
         << data.escF1->comm_pwm << ",";

    file << data.escF2->voltage << ","
         << data.escF2->bus_current << ","
         << data.escF2->current << ",";

    file << static_cast<int>(data.escF3->cap_temp) << ","
         << static_cast<int>(data.escF3->mcu_temp) << ","
         << static_cast<int>(data.escF3->motor_temp) << ","
         << data.escF3->Error;

    file << "\n";
}

uint64_t UnifiedCsvWriter::getCurrentTimeMillis() const {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
