#include "EscStatus2.h"

#include "Frames.h"

EscSensors::EscStatus2::EscStatus2()
{
    nameFrame = "ESC Питание";
    orderedNames = {"Bus voltage", "Bus current", "Motor line current"};

    for (auto &it : orderedNames)
        fields[it].val = 0;
}

void EscSensors::EscStatus2::setData(std::string_view data)
{
    EscStatusInfo2 tempStatus2 = EscStatusInfo2::unpack(reinterpret_cast<const char*>(data.data()));
    fields["Bus voltage"].val = static_cast<double>(tempStatus2.voltage);
    fields["Bus current"].val = static_cast<double>(tempStatus2.bus_current);
    fields["Motor line current"].val = static_cast<double>(tempStatus2.current);
}
