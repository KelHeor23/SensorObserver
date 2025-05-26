#ifndef ESCSENSORS_H
#define ESCSENSORS_H

#include <string_view>
#include <unordered_map>
#include <vector>

#include "../Sensors.h"

namespace EscSensors {

namespace {
    std::vector<SensorName> orderedNames = {"RPM motor speed", "recv_pwm", "comm_pwm", "Bus voltage", "Bus current", "Motor line current", "cap_temp", "mcu_temp", "motor_temp", "Error"};
};

class EscSensors
{

public:
    EscSensors();

    void setData(uint16_t frame_id, std::string_view data);

    std::unordered_map<SensorName, double> getSensorsData() const;

private:
    std::unordered_map<SensorName, double> sensorsData;
};

}


#endif // ESCSENSORS_H
