#ifndef SENSORS_H
#define SENSORS_H

#include <QString>

using SensorName = std::string;

struct SensorLimits {
    int min = 0;
    int max = 0;
};

struct SensorData {
    SensorLimits limit;
    int val = 0;
};

#endif // SENSORS_H
