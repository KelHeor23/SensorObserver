#ifndef SAVETOCSV_H
#define SAVETOCSV_H

#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Data/Frames/Frames.h"

// Класс для объединенных данных устройства
struct DeviceData {
    std::shared_ptr<EngineSensorsData> engine;
    std::shared_ptr<VoltageRegulatorsData> regulator;
    std::shared_ptr<OtherSensorsData> other;
    std::shared_ptr<EscSensors::EscStatusInfo1> escF1 = std::make_shared<EscSensors::EscStatusInfo1>();
    std::shared_ptr<EscSensors::EscStatusInfo2> escF2 = std::make_shared<EscSensors::EscStatusInfo2>();
    std::shared_ptr<EscSensors::EscStatusInfo3> escF3 = std::make_shared<EscSensors::EscStatusInfo3>();
    uint64_t last_update = 0;
};

class UnifiedCsvWriter {
private:
    UnifiedCsvWriter(uint64_t flush_interval_ms = 20);

public:
    static UnifiedCsvWriter& Instance(){
        static UnifiedCsvWriter temp;
        return temp;
    }

    ~UnifiedCsvWriter();

    void addEngineData(std::shared_ptr<EngineSensorsData> data);
    void addRegulatorData(std::shared_ptr<VoltageRegulatorsData> data);
    void addOtherSensorsData(std::shared_ptr<OtherSensorsData> data);
    void addEscF1Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo1> data);
    void addEscF2Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo2> data);
    void addEscF3Data(uint8_t device_id, std::shared_ptr<EscSensors::EscStatusInfo3> data);

    void stop();

private:
    std::string buildCSVheader(const std::vector<std::vector<std::string>>& vectors);
    std::string formatTimeWithMilliseconds(long long ms_since_epoch);

    void run();

    void flushAllData();

    void writeDeviceData(std::ofstream& file, uint8_t device_id, const DeviceData& data, bool isCustom);

    uint64_t getCurrentTimeMillis() const;

    std::string getNewName();

private:

    std::string m_filename;
    uint64_t m_flush_interval;
    std::atomic<bool> m_running;
    std::atomic<bool> m_updated{false};
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::unordered_map<uint8_t, DeviceData> m_deviceDataESC;
    std::unordered_map<uint8_t, DeviceData> m_deviceDataCustom;
};

#endif // SAVETOCSV_H
