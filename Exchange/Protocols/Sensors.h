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

struct SensorSharedSettings {
    bool useDetalaizedLimits = false; // Теперь разделяемое поле
};

struct SensorData {
    std::shared_ptr<SensorLimits> limit; // Общий ресурс
    std::shared_ptr<std::vector<SensorLimitsColored>> detalaizedLimits;
    std::shared_ptr<SensorSharedSettings> settings; // Общий ресурс

    int val = 0;

    SensorData() {
        limit = std::make_shared<SensorLimits>();
        detalaizedLimits = std::make_shared<std::vector<SensorLimitsColored>>();
        settings = std::make_shared<SensorSharedSettings>();
    }

    void linkLimits(std::shared_ptr<SensorData> other) {
        limit = other->limit;  // Используем тот же shared_ptr
    }

    void linkDetalaizedLimits(std::shared_ptr<SensorData> other) {
        detalaizedLimits = other->detalaizedLimits;  // Используем тот же shared_ptr
    }

    void linkSettings(std::shared_ptr<SensorData> other) {
        settings = other->settings;
    }

    void linksSensorData(std::shared_ptr<SensorData> other) {
        limit = other->limit;  // Используем тот же shared_ptr
        detalaizedLimits = other->detalaizedLimits;  // Используем тот же shared_ptr
        settings = other->settings;
    }
};

#endif // SENSORS_H
