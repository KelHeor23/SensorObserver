#include "EngineSensors.h"

namespace EngineSensors {

EngineSensors::EngineSensors(){
}

void EngineSensors::setData(std::string_view data)
{
    if (data.size() < sizeof(EngineSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    const EngineSensorsData* receivedData = reinterpret_cast<const EngineSensorsData*>(data.data());

    sensorsData["Обороты"]          = static_cast<int>(receivedData->speed);
    sensorsData["Температура"]      = static_cast<int>(receivedData->temperature);
    sensorsData["Угол биения"]      = static_cast<int>(receivedData->runoutAngle);
    sensorsData["Амплитуда биения"] = static_cast<int>(receivedData->runoutAmplitude);
}

void EngineSensors::setSensorsDataLimits(Limits *newSensorsDataLimits)
{
    sensorsDataLimits = newSensorsDataLimits;
}

std::unordered_map<std::string, int> EngineSensors::getSensorsData() const
{
    return sensorsData;
}

Limits *EngineSensors::getSensorsDataLimits() const
{
    return sensorsDataLimits;
}

Limits::Limits()
{
}

}
