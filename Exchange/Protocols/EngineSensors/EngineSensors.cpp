#include "EngineSensors.h"

EngineSensors::EngineSensors() {
    sensorsData.push_back(NodeSensor{"Обороты", 0, 0});
    sensorsData.push_back(NodeSensor{"Температура", 0, 0});
    sensorsData.push_back(NodeSensor{"Угол биения", 0, 0});
    sensorsData.push_back(NodeSensor{"Амплитуда биения", 0, 0});
}

void EngineSensors::setData(std::string_view data)
{
    engineSensorsData.parseEngineSensorsData(data);
}

void EngineSensors::EngineSensorsData::parseEngineSensorsData(std::string_view data)
{
    if (data.size() < sizeof(EngineSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    memcpy(this, data.data(), sizeof(EngineSensorsData));
}
