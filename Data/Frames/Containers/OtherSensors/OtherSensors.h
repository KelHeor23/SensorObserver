#ifndef OTHERSENSORS_H
#define OTHERSENSORS_H

#include <vector>

#include "Data/Frames/Containers/Base.h"

static std::vector<SensorName> sensorNames = {"Тяга"};

namespace OtherSensors {
class OtherSensors : public BaseProtocol
{
public:
    OtherSensors();

    void setData(std::string_view data, int16_t node_id) override;
};
}
#endif // OTHERSENSORS_H
