#include "OtherSensors.h"

#include "Tools/SaveToCSV.h"
#include "Data/DataStructure.h"

namespace OtherSensors {

OtherSensors::OtherSensors() {
    nameFrame = "Остальные датчики";
    orderedNames = sensorNames;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}

void OtherSensors::setData(std::string_view data, int16_t node_id)
{
    if (data.size() < sizeof(OtherSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    auto receivedData = std::make_shared<OtherSensorsData>();
    memcpy(receivedData.get(), data.data(), sizeof(OtherSensorsData));

    fields["Реакт. мом. двиг 1"]->val = static_cast<double>(receivedData->reactiveTorquEngine1);
    fields["Реакт. мом. двиг 2"]->val = static_cast<double>(receivedData->reactiveTorquEngine2);
    fields["Тяга 1"]->val = static_cast<double>(receivedData->thrustEngine1);
    fields["Тяга 2"]->val = static_cast<double>(receivedData->thrustEngine2);

    UnifiedCsvWriter::Instance().addOtherSensorsData(receivedData);
    DataStructure::Instance().addData(node_id, nameFrame, OTHER_SENSROS, receivedData);
}
}
