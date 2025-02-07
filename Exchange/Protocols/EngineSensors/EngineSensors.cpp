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



    size_t offset = 0;

    uint32_t    canID_temp; // Пока никак не используется
    memcpy(&canID_temp, it + offset, sizeof(EngineSensorsData::canID));
    offset += sizeof(EngineSensorsData::canID);

    memcpy(&sensorsData["Обороты"], it + offset, sizeof(EngineSensorsData::speed));
    offset += sizeof(EngineSensorsData::speed);

    memcpy(&sensorsData["Температура"], it + offset, sizeof(EngineSensorsData::temperature));
    offset += sizeof(EngineSensorsData::temperature);

    memcpy(&sensorsData["Угол биения"], it + offset, sizeof(EngineSensorsData::runoutAngle));
    offset += sizeof(EngineSensorsData::runoutAngle);

    memcpy(&sensorsData["Амплитуда биения"], it + offset, sizeof(EngineSensorsData::runoutAmplitude));
    offset += sizeof(EngineSensorsData::runoutAmplitude);

    //memcpy(this, data.data(), sizeof(EngineSensorsData));
}

void EngineSensors::setSensorsDataLimits(Limits *newSensorsDataLimits)
{
    sensorsDataLimits = newSensorsDataLimits;
}

Limits::Limits()
{
    for (auto &it : orderedNames)
        sensorsDataLimits.insert({it, SensorLimits{0,0}});
}

}
