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

    fields["Тяга"]->val = static_cast<int>(receivedData->weight);

    UnifiedCsvWriter::Instance().addOtherSensorsData(receivedData);
    DataStructure::Instance().addData(node_id, nameFrame, OTHER_SENSROS, receivedData);
}
}
