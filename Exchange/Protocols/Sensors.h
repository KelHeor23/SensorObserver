#ifndef SENSORS_H
#define SENSORS_H

#include "qcolor.h"
#include <QString>
#include <memory>

using SensorName = std::string;

struct SensorLimits {
    int min = 0;
    int max = 0;
};

struct SensorLimitsColored {
    SensorLimits limit;
    QColor color;
};

struct SensorData {
    std::shared_ptr<SensorLimits> limit; // Общий ресурс
    std::shared_ptr<QList<SensorLimitsColored>> detalaizedLimits;

    bool useDetalaizedLimits = false;
    int val = 0;

    SensorData() {
        limit = std::make_shared<SensorLimits>();
    }

    void linkLimits(SensorData& other) {
        limit = other.limit;  // Используем тот же shared_ptr
    }

    void linkDetalaizedLimits(SensorData& other) {
        detalaizedLimits = other.detalaizedLimits;  // Используем тот же shared_ptr
    }
};

#endif // SENSORS_H
