#ifndef ESCSTATUS3_H
#define ESCSTATUS3_H

#include "Exchange/Protocols/Base.h"

namespace EscSensors {

static std::vector<SensorName> sensorNamesFrame3 = {"cap_temp", "mcu_temp", "motor_temp", "Error"};

class EscStatus3 : public BaseProtocol
{
public:
    EscStatus3();
    void setData(std::string_view data, int16_t node_id) override;
};
}

#endif // ESCSTATUS3_H
