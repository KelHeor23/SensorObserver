#include "EngineSensors.h"

namespace EngineSensors {

EngineSensors::EngineSensors(){
    nameFrame = "Датчики двигателя";
    orderedNames = {"Обороты", "Температура", "Угол биения", "Амплитуда биения"};
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

    fields["Обороты"].val          = static_cast<int>(receivedData->speed);
    fields["Температура"].val      = static_cast<int>(receivedData->temperature);
    fields["Угол биения"].val      = static_cast<int>(receivedData->runoutAngle);
    fields["Амплитуда биения"].val = static_cast<int>(receivedData->runoutAmplitude);
}

std::unordered_map<SensorName, int> EngineSensors::getSensorsData() const
{
    return sensorsData;
}

}
