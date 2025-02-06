#include "EngineSensors.h"

EngineSensors::Limits::Limits()
{
    for (auto it : SensorsList)
        sensorsDataLimits.push_back(SensorLimits{it, 0, 0});
}

EngineSensors::EngineSensors::EngineSensors()
{

}
/*
void EngineSensors::EngineSensors::setData(std::string_view data)
{
}

void EngineSensors::EngineSensors::setSensorsDataLimits(const std::vector<NodeSensorsLimits> &newSensorsDataLimits)
{
    sensorsDataLimits = newSensorsDataLimits;
}

void EngineSensors::EngineSensors::EngineSensorsData::parseEngineSensorsData(std::string_view data)
{
    if (data.size() < sizeof(EngineSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    memcpy(this, data.data(), sizeof(EngineSensorsData));
}*/

void EngineSensors::EngineSensors::setSensorsDataLimits(std::vector<SensorLimits> *newSensorsDataLimits)
{
    sensorsDataLimits = newSensorsDataLimits;
}
