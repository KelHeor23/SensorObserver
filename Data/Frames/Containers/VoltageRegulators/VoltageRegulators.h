#ifndef VOLTAGEREGULATORS_H
#define VOLTAGEREGULATORS_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "Exchange/Protocols/Sensors.h"
#include "Exchange/Protocols/Base.h"

namespace VoltageRegulators {

static std::vector<SensorName> sensorNames = {"Среднее напряжение A", "Среднее напряжение B", "Среднее напряжение C"};

class VoltageRegulators : public BaseProtocol
{
public:
    VoltageRegulators();

    void setData(std::string_view data, int16_t node_id) override;
};

};


#endif // VOLTAGEREGULATORS_H
