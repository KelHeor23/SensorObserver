#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H


#include "Exchange/Protocols/SensorsFrames.h"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class DataStructure
{
    using SensorName    = std::string;
    using FrameName     = FrameTypes;
    using Data          = std::vector<uint64_t>;
    using SensorData    = std::unordered_map<SensorName, Data>;         // датчик и все пришедшие данные данные
    using FrameData     = std::unordered_map<FrameName, SensorData>;    // база всех данных датчиков

public:
    DataStructure();
    void addData(size_t engineNum, FrameTypes type, BaseFrame *data);

public:
    void addEngineSensorsData(size_t engineNum, EngineSensorsData *data);

public:
    std::vector<FrameData> engines; // вектор объединяющий
};

#endif // DATASTRUCTURE_H
