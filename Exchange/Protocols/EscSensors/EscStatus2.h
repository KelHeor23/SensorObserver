#ifndef ESCSTATUS2_H
#define ESCSTATUS2_H

#include "Exchange/Protocols/Base.h"

namespace EscSensors {

static std::vector<SensorName> sensorNamesFrame2 = {"Bus voltage", "Bus current", "Motor line current"};

class EscStatus2 : public BaseProtocol
{
public:
    EscStatus2();
    void setData(std::string_view data, int16_t node_id) override;
};
}

#endif // ESCSTATUS2_H
