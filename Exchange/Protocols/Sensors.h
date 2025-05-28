#ifndef SENSORS_H
#define SENSORS_H

#include <QString>
#include <memory>

using SensorName = std::string;

struct SensorLimits {
    int min = 0;
    int max = 0;
};

struct SensorData {
    std::shared_ptr<SensorLimits> limit; // Общий ресурс
    int val = 0;

    SensorData() {
        limit = std::make_shared<SensorLimits>();
    }
};

#endif // SENSORS_H
