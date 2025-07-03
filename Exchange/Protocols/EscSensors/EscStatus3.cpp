#include "EscStatus3.h"

#include "Frames.h"
#include "Tools/SaveToCSV.h"

EscSensors::EscStatus3::EscStatus3()
{
    nameFrame = "ESC Температуры";
    orderedNames = sensorNamesFrame3;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}

void EscSensors::EscStatus3::setData(std::string_view data, int16_t node_id)
{
    EscStatusInfo3 tempStatus3 = EscStatusInfo3::unpack(reinterpret_cast<const char*>(data.data()));
    fields["cap_temp"]->val = static_cast<double>(tempStatus3.cap_temp);
    fields["mcu_temp"]->val = static_cast<double>(tempStatus3.mcu_temp);
    fields["motor_temp"]->val = static_cast<double>(tempStatus3.motor_temp);
    fields["Error"]->val = static_cast<double>(tempStatus3.Error);

    UnifiedCsvWriter::Instance().addEscF3Data(node_id, std::move(tempStatus3));
}
