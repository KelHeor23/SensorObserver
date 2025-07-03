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
#include <optional>

#include "Exchange/Protocols/EngineSensors/EngineSensors.h"
#include "Exchange/Protocols/VoltageRegulators/VoltageRegulators.h"
#include "Exchange/Protocols/EscSensors/Frames.h"

// Класс для объединенных данных устройства
struct DeviceData {
    std::optional<EngineSensors::EngineSensorsData> engine;
    std::optional<VoltageRegulators::VoltageRegulatorsData> regulator;
    std::optional<EscSensors::EscStatusInfo1> escF1;
    std::optional<EscSensors::EscStatusInfo2> escF2;
    std::optional<EscSensors::EscStatusInfo3> escF3;
    uint64_t last_update = 0;
};

class UnifiedCsvWriter {
private:
    UnifiedCsvWriter(const std::string& filename, uint64_t flush_interval_ms = 20);

public:
    static UnifiedCsvWriter& Instance(){
        static UnifiedCsvWriter temp("sensors.csv");
        return temp;
    }

    ~UnifiedCsvWriter();

    void addEngineData(const EngineSensors::EngineSensorsData& data);
    void addRegulatorData(const VoltageRegulators::VoltageRegulatorsData& data);
    void addEscF1Data(uint8_t device_id, const EscSensors::EscStatusInfo1&& data);
    void addEscF2Data(uint8_t device_id, const EscSensors::EscStatusInfo2&& data);
    void addEscF3Data(uint8_t device_id, const EscSensors::EscStatusInfo3&& data);

    void stop();

private:
    std::string buildCSVheader(const std::vector<std::vector<std::string>>& vectors);
    std::string formatTimeWithMilliseconds(long long ms_since_epoch);

    void run();

    void flushAllData();

    void writeDeviceData(std::ofstream& file, uint8_t device_id, const DeviceData& data);

    uint64_t getCurrentTimeMillis() const;

    std::string m_filename;
    uint64_t m_flush_interval;
    std::atomic<bool> m_running;
    std::atomic<bool> m_updated{false};
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::unordered_map<uint8_t, DeviceData> m_deviceData;
};

#endif // SAVETOCSV_H
