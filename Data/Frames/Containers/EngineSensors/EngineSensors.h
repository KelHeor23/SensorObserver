#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <vector>

#include "Data/Frames/Containers/Base.h"

namespace EngineSensors {

static std::vector<SensorName> sensorNames = {"Угол биения", "Амплитуда биения"};

class EngineSensors : public BaseProtocol
{
public:
    EngineSensors();

    void setData(std::string_view data, int16_t node_id) override;
};
};



#endif // ENGINESENSORS_H
