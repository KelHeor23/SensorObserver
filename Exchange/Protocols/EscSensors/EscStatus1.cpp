#include "EscStatus1.h"

#include "Frames.h"

EscSensors::EscStatus1::EscStatus1()
{
    nameFrame = "ESC Мотор";
    orderedNames = {"RPM motor speed", "recv_pwm", "comm_pwm"};

    for (auto &it : orderedNames)
        fields[it].val = 0;
}

void EscSensors::EscStatus1::setData(std::string_view data)
{
    EscStatusInfo1 tempStatus1 = EscStatusInfo1::unpack(reinterpret_cast<const char*>(data.data()));
    fields["RPM motor speed"].val = static_cast<double>(tempStatus1.speed);
    fields["recv_pwm"].val = static_cast<double>(tempStatus1.recv_pwm);
    fields["comm_pwm"].val = static_cast<double>(tempStatus1.comm_pwm);
}
