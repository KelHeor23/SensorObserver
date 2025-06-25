#include "EscStatus2.h"

#include "Frames.h"
#include "Tools/SaveToCSV.h"

EscSensors::EscStatus2::EscStatus2()
{
    nameFrame = "ESC Питание";
    orderedNames = {"Bus voltage", "Bus current", "Motor line current"};

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}

void EscSensors::EscStatus2::setData(std::string_view data, int16_t node_id)
{
    EscStatusInfo2 tempStatus2 = EscStatusInfo2::unpack(reinterpret_cast<const char*>(data.data()));
    fields["Bus voltage"]->val = static_cast<double>(tempStatus2.voltage);
    fields["Bus current"]->val = static_cast<double>(tempStatus2.bus_current);
    fields["Motor line current"]->val = static_cast<double>(tempStatus2.current);

    UnifiedCsvWriter::Instance().addEscF2Data(node_id, std::move(tempStatus2));
}
