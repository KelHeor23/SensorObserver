#include "EscSensors.h"

#include "Frames.h"

namespace EscSensors {
EscSensors::EscSensors() {
    nameFrame = "Датчики ESC";
    orderedNames = {"RPM motor speed", "recv_pwm", "comm_pwm", "Bus voltage", "Bus current", "Motor line current", "cap_temp", "mcu_temp", "motor_temp", "Error"};

    for (auto &it : orderedNames)
        fields[it].val = 0;
}

void EscSensors::setData(std::string_view data)
{

}

void EscSensors::setDataESC(uint16_t frame_id, std::string_view data)
{
    switch(frame_id){
    case 20022: {
        EscStatusInfo1 tempStatus1 = EscStatusInfo1::unpack(reinterpret_cast<const char*>(data.data()));
        fields["RPM motor speed"].val = static_cast<double>(tempStatus1.speed);
        fields["recv_pwm"].val = static_cast<double>(tempStatus1.recv_pwm);
        fields["comm_pwm"].val = static_cast<double>(tempStatus1.comm_pwm);
        break;
    }
    case 20023: {
        EscStatusInfo2 tempStatus2 = EscStatusInfo2::unpack(reinterpret_cast<const char*>(data.data()));
        fields["Bus voltage"].val = static_cast<double>(tempStatus2.voltage);
        fields["Bus current"].val = static_cast<double>(tempStatus2.bus_current);
        fields["Motor line current"].val = static_cast<double>(tempStatus2.current);
        break;
    }
    case 20024: {
        EscStatusInfo3 tempStatus3 = EscStatusInfo3::unpack(reinterpret_cast<const char*>(data.data()));
        fields["cap_temp"].val = static_cast<double>(tempStatus3.cap_temp);
        fields["mcu_temp"].val = static_cast<double>(tempStatus3.mcu_temp);
        fields["motor_temp"].val = static_cast<double>(tempStatus3.motor_temp);
        fields["Error"].val = static_cast<double>(tempStatus3.Error);
        break;
    }
    default: break;
    }
}
}
