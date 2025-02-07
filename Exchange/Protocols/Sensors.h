#ifndef SENSORS_H
#define SENSORS_H

#include <QString>

struct NameSensor {
    size_t orderNum;
    QString name;
};

struct SensorLimits {
    int min = 0;
    int max = 0;
};

struct SensorData {
    SensorLimits limit;
    int val = 0;
};

#endif // SENSORS_H
