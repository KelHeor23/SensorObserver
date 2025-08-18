#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <QVector>

#include "Frames.h"

class DataStructure
{
    using SensorName    = std::string;
    using FrameName     = std::string;
    using Data          = QVector<double>;
    using SensorData    = std::unordered_map<SensorName, Data>;         // датчик и все пришедшие данные данные
    using FrameData     = std::unordered_map<FrameName, SensorData>;    // база всех данных датчиков



public:
    static DataStructure& Instance(){
        static DataStructure obj;
        return obj;
    };

    void addData(size_t engineNum, FrameTypes type, BaseFrame *data);

private:
    DataStructure();

    template<typename T>
    void addValueToFrame(size_t engineNum, FrameTypes type, const std::string& key, T value);

    void addEngineSensorsData(size_t engineNum, EngineSensorsData *data);
    void addVoltageRegulatorSensorsData(size_t engineNum, VoltageRegulatorsData *data);
    void addEscStatusInfo1Data(size_t engineNum, EscSensors::EscStatusInfo1 *data);
    void addEscStatusInfo2Data(size_t engineNum, EscSensors::EscStatusInfo2 *data);
    void addEscStatusInfo3Data(size_t engineNum, EscSensors::EscStatusInfo3 *data);

public:
    std::vector<FrameData> engines; // вектор объединяющий
};

#endif // DATASTRUCTURE_H
