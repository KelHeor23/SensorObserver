#include "SaveToCSV.h"
#include "Exchange/Protocols/EscSensors/EscStatus1.h"
#include "Exchange/Protocols/EscSensors/EscStatus2.h"
#include "Exchange/Protocols/EscSensors/EscStatus3.h"

UnifiedCsvWriter::UnifiedCsvWriter(const std::string &filename, uint64_t flush_interval_ms)
    : m_filename(filename), m_flush_interval(flush_interval_ms),
    m_running(true), m_thread(&UnifiedCsvWriter::run, this) {
    // Запись заголовка CSV
    std::ofstream file(m_filename, std::ios::out);
    if (file.is_open()) {
        file << buildCSVheader({{"time", "device_id"}
                                , EngineSensors::sensorNames, VoltageRegulators::sensorNames
                                , EscSensors::sensorNamesFrame1, EscSensors::sensorNamesFrame2
                                , EscSensors::sensorNamesFrame3});
    }
}

UnifiedCsvWriter::~UnifiedCsvWriter() {
    stop();
}

void UnifiedCsvWriter::addEngineData(const EngineSensors::EngineSensorsData& data) {
    const uint8_t device_id = data.canID & 0x07;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceData[device_id].engine = data;
    m_deviceData[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addRegulatorData(const VoltageRegulators::VoltageRegulatorsData& data) {
    const uint8_t device_id = data.canID & 0x07;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceData[device_id].regulator = data;
    m_deviceData[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addEscF1Data(uint8_t device_id, const EscSensors::EscStatusInfo1&& data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceData[device_id].escF1 = data;
    m_deviceData[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addEscF2Data(uint8_t device_id, const EscSensors::EscStatusInfo2&& data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceData[device_id].escF2 = data;
    m_deviceData[device_id].last_update = getCurrentTimeMillis();
    m_updated = true;
    m_cv.notify_one();
}

void UnifiedCsvWriter::addEscF3Data(uint8_t device_id, const EscSensors::EscStatusInfo3&& data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceData[device_id].escF3 = data;
    m_deviceData[device_id].last_update = getCurrentTimeMillis();
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
    for (auto& [device_id, data] : m_deviceData) {
        // Пропуск устаревших или неполных данных
        if (current_time - data.last_update > m_flush_interval * 5) continue;

        writeDeviceData(file, device_id, data);
    }
    file.flush();
}

void UnifiedCsvWriter::writeDeviceData(std::ofstream &file, uint8_t device_id, const DeviceData &data) {
    file << data.last_update << "," << static_cast<int>(device_id) << ",";

    // Engine данные
    if (data.engine) {
        file << data.engine->speed << ","
             << static_cast<int>(data.engine->temperature) << ","
             << data.engine->runoutAngle << ","
             << data.engine->runoutAmplitude << ",";
    } else {
        file << ",,,,";
    }

    // Регулятор данные
    if (data.regulator) {
        file << static_cast<int>(data.regulator->inputVoltageHP) << ","
             << static_cast<int>(data.regulator->inputVoltageLP) << ","
             << static_cast<int>(data.regulator->electricCurrent) << ","
             << data.regulator->controlPWM << ","
             << static_cast<int>(data.regulator->averageVoltageA) << ","
             << static_cast<int>(data.regulator->averageVoltageB) << ","
             << static_cast<int>(data.regulator->averageVoltageC) << ",";
    } else {
        file << ",,,,,,,";
    }

    // ESC1 данные
    if (data.escF1) {
        file << data.escF1->speed << ","
             << data.escF1->recv_pwm << ","
             << data.escF1->comm_pwm << ",";
    } else {
        file << ",,,";
    }

    // ESC2 данные
    if (data.escF2) {
        file << data.escF2->voltage << ","
             << data.escF2->bus_current << ","
             << data.escF2->current << ",";
    } else {
        file << ",,,";
    }

    // ESC3 данные
    if (data.escF3) {
        file << data.escF3->cap_temp << ","
             << data.escF3->mcu_temp << ","
             << data.escF3->motor_temp << ","
             << data.escF3->Error;
    } else {
        file << ",,,";
    }

    file << "\n";
}

uint64_t UnifiedCsvWriter::getCurrentTimeMillis() const {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
