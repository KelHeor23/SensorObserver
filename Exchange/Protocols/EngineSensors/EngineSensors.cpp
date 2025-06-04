#include "EngineSensors.h"

namespace EngineSensors {

EngineSensors::EngineSensors(){
    nameFrame = "Датчики двигателя";
    orderedNames = {"Обороты", "Температура", "Угол биения", "Амплитуда биения"};

    for (auto &it : orderedNames)
        fields[it].val = 0;
}

void EngineSensors::setData(std::string_view data)
{
    if (data.size() < sizeof(EngineSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    const EngineSensorsData* receivedData = reinterpret_cast<const EngineSensorsData*>(data.data());

    fields["Обороты"].val          = static_cast<int>(receivedData->speed);
    fields["Температура"].val      = static_cast<int>(receivedData->temperature);
    fields["Угол биения"].val      = static_cast<int>(receivedData->runoutAngle);
    fields["Амплитуда биения"].val = static_cast<int>(receivedData->runoutAmplitude);
}

}
