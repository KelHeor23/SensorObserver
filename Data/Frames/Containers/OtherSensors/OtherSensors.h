#ifndef OTHERSENSORS_H
#define OTHERSENSORS_H

#include <vector>

#include "Data/Frames/Containers/Base.h"

static std::vector<SensorName> sensorNames = {"Реакт. мом. двиг 1", "Реакт. мом. двиг 2", "Тяга 1", "Тяга 2"};

namespace OtherSensors {
class OtherSensors : public BaseProtocol
{
public:
    OtherSensors();

    void setData(std::string_view data, int16_t node_id) override;
};
}
#endif // OTHERSENSORS_H
