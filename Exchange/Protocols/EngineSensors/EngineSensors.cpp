#include "EngineSensors.h"

namespace EngineSensors {

Limits::Limits()
{
    for (auto it : SensorsList)
        sensorsDataLimits.push_back(SensorLimits{it, 0, 0});
}
EngineSensors::EngineSensors(){
    sensorsDataLimits = new Limits;
}

void EngineSensors::setData(std::string_view data)
{
    sensorsData.parseEngineSensorsData(data);
}

EngineSensors::EngineSensorsData EngineSensors::getSensorsData() const
{
    return sensorsData;
}

Limits *EngineSensors::getSensorsDataLimits() const
{
    return sensorsDataLimits;
}

void EngineSensors::setSensorsDataLimits(Limits *newSensorsDataLimits)
{
    sensorsDataLimits = newSensorsDataLimits;
}

void EngineSensors::EngineSensorsData::parseEngineSensorsData(std::string_view data)
{
    if (data.size() < sizeof(EngineSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    memcpy(this, data.data(), sizeof(EngineSensorsData));
}

}
