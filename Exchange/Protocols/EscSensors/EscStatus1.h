#ifndef ESCSTATUS1_H
#define ESCSTATUS1_H

#include "Exchange/Protocols/Base.h"

namespace EscSensors {

static std::vector<SensorName> sensorNamesFrame1 = {"RPM motor speed", "recv_pwm", "comm_pwm"};

class EscStatus1 : public BaseProtocol
{
public:
    EscStatus1();
    void setData(std::string_view data, int16_t node_id) override;
};
}


#endif // ESCSTATUS1_H
