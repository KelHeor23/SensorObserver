#include "EscStatus3.h"

#include "Frames.h"

EscSensors::EscStatus3::EscStatus3()
{
    nameFrame = "ESC Температуры";
    orderedNames = {"cap_temp", "mcu_temp", "motor_temp", "Error"};

    for (auto &it : orderedNames)
        fields[it].val = 0;
}

void EscSensors::EscStatus3::setData(std::string_view data)
{
    EscStatusInfo3 tempStatus3 = EscStatusInfo3::unpack(reinterpret_cast<const char*>(data.data()));
    fields["cap_temp"].val = static_cast<double>(tempStatus3.cap_temp);
    fields["mcu_temp"].val = static_cast<double>(tempStatus3.mcu_temp);
    fields["motor_temp"].val = static_cast<double>(tempStatus3.motor_temp);
    fields["Error"].val = static_cast<double>(tempStatus3.Error);
}
