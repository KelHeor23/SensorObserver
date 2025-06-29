#include "EngineSensors.h"
#include "Tools/SaveToCSV.h"

namespace EngineSensors {

EngineSensors::EngineSensors(){
    nameFrame = "Датчики двигателя";
    orderedNames = sensorNames;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}

void EngineSensors::setData(std::string_view data, int16_t node_id)
{
    if (data.size() < sizeof(EngineSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    const EngineSensorsData* receivedData = reinterpret_cast<const EngineSensorsData*>(data.data());

    fields["Обороты"]->val          = static_cast<int>(receivedData->speed);
    fields["Температура"]->val      = static_cast<int>(receivedData->temperature);
    fields["Угол биения"]->val      = static_cast<int>(receivedData->runoutAngle);
    fields["Амплитуда биения"]->val = static_cast<int>(receivedData->runoutAmplitude);

    UnifiedCsvWriter::Instance().addEngineData(*receivedData);
}

}
