#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <vector>

#include "Sensors.h"

class EngineSensors: public Sensors
{
public:
    EngineSensors();

    std::vector<NodeSensor> sensorsData;
};

#endif // ENGINESENSORS_H
