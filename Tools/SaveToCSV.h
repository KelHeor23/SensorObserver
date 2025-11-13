/**
 * \file SaveToCSV.h
 * \brief Единый потокобезопасный писатель CSV для телеметрии.
 * \details Собирает данные по устройствам (ESC/двигатель/регуляторы) и периодически сбрасывает в CSV в отдельном потоке.
 */

#ifndef SAVETOCSV_H
#define SAVETOCSV_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cstdint>
#include <unordered_map>
#include <vector>
#endif

#include "Data/Frames/Frames.h"

// Класс для объединенных данных устройства
struct DeviceData {
    std::shared_ptr<EngineSensorsData> engine           = std::make_shared<EngineSensorsData>();
    std::shared_ptr<VoltageRegulatorsData> regulator    = std::make_shared<VoltageRegulatorsData>();
    std::shared_ptr<OtherSensorsData> other             = std::make_shared<OtherSensorsData>();
    std::shared_ptr<EscSensors::EscStatusInfo1> escF1   = std::make_shared<EscSensors::EscStatusInfo1>();
    std::shared_ptr<EscSensors::EscStatusInfo2> escF2   = std::make_shared<EscSensors::EscStatusInfo2>();
    std::shared_ptr<EscSensors::EscStatusInfo3> escF3   = std::make_shared<EscSensors::EscStatusInfo3>();
    uint64_t last_update = 0;
};
/**
 * \class UnifiedCsvWriter
 * \brief Потокобезопасная запись телеметрии в CSV с объединением по устройствам.
 * \details Работает в отдельном потоке, по таймеру/сигналу формирует строки и сбрасывает их на диск.
 */

class UnifiedCsvWriter {
private:
    UnifiedCsvWriter(uint64_t flush_interval_ms = 20);

public:
    static UnifiedCsvWriter& Instance(){
        static UnifiedCsvWriter temp;
        return temp;
    }

    ~UnifiedCsvWriter();
    /** \brief Добавляет данные датчиков двигателя. */
    void addEngineData(std::shared_ptr<EngineSensorsData> data);
    /** \brief Добавляет данные регуляторов питания. */
    void addRegulatorData(std::shared_ptr<VoltageRegulatorsData> data);
    /** \brief Добавляет данные прочих датчиков. */
    void addOtherSensorsData(std::shared_ptr<OtherSensorsData> data);
    /** \brief Добавляет данные кадра ESC Status1 для устройства. */
    void addEscF1Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo1> data);
    /** \brief Добавляет данные кадра ESC Status2 для устройства. */
    void addEscF2Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo2> data);
    /** \brief Добавляет данные кадра ESC Status3 для устройства. */
    void addEscF3Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo3> data);

    void stop();

private:
    std::string buildCSVheader(const std::vector<std::vector<std::string>>& vectors);
    std::string formatTimeWithMilliseconds(long long ms_since_epoch);
    /** \brief Фоновая функция рабочего потока, которая ждёт обновлений и пишет CSV. */

    void run();

    void flushAllData();

    void writeDeviceData(std::ofstream& file, uint8_t device_id, const DeviceData& data, bool isCustom);

    uint64_t getCurrentTimeMillis() const;

    std::string getNewName();

private:
    /** Имя CSV-файла. */

    std::string m_filename;
    /** Интервал сброса на диск (мс). */
    uint64_t m_flush_interval;
    /** Флаг работы фонового потока. */
    std::atomic<bool> m_running;
    /** Флаг наличия новых данных для записи. */
    std::atomic<bool> m_updated{false};
    /** Поток записи CSV. */
    std::thread m_thread;
    /** Мьютекс защиты общих структур данных. */
    std::mutex m_mutex;
    /** Условная переменная для ожидания обновлений/тайм‑аута. */
    std::condition_variable m_cv;
    /** Данные устройств ESC по node_id. */
    std::unordered_map<uint8_t, DeviceData> m_deviceDataESC;
    /** Данные «кастомных» устройств (двигатели/регуляторы) по node_id. */
    std::unordered_map<uint8_t, DeviceData> m_deviceDataCustom;
};

#endif // SAVETOCSV_H

