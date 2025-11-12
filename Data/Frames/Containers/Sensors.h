/**
 * \file Sensors.h
 * \brief Структуры описания сенсора: пределы, раскраска, настройки и данные.
 * \details Определяет ограничения, цветовые зоны, параметры отображения и контейнер значений для UI/логики.
 */

#ifndef SENSORS_H
#define SENSORS_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "qcolor.h"
#include <QString>
#include <memory>
#endif
/**
 * \struct SensorLimits
 * \brief Целочисленные пределы допустимых значений для сенсора.
 * \details Используются для базовой валидации и отображения шкалы.
 */

struct SensorLimits {
    int min = 0;
    int max = 0;
};
/**
 * \struct SensorLimitsColored
 * \brief Пределы с привязкой цвета для подсветки зон в UI.
 */

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

    std::atomic<double> val = 0;

    SensorData() {
        limit = std::make_shared<SensorLimits>();
        detalaizedLimits = std::make_shared<std::vector<SensorLimitsColored>>();
        settings = std::make_shared<SensorSharedSettings>();
    }

    SensorData& operator=(const SensorData& other) {
        if (this != &other) {
            limit = other.limit;
            detalaizedLimits = other.detalaizedLimits;
            settings = other.settings;
            val.store(other.val.load());
        }
        return *this;
    }

    void linkLimits(std::shared_ptr<SensorData> other) {
        limit = other->limit;  // Используем тот же shared_ptr
    }

    void linkDetalaizedLimits(std::shared_ptr<SensorData> other) {
        detalaizedLimits = other->detalaizedLimits;  // Используем тот же shared_ptr
    }
    /** \brief Связывает настройки (settings) с другим объектом сенсора. */

    void linkSettings(std::shared_ptr<SensorData> other) {
        settings = other->settings;
    }
    /** \brief Разделяет лимиты и настройки с другим сенсором (использует те же shared_ptr). */

    void linksSensorData(std::shared_ptr<SensorData> other) {
        limit = other->limit;  // Используем тот же shared_ptr
        detalaizedLimits = other->detalaizedLimits;  // Используем тот же shared_ptr
        settings = other->settings;
    }
};

#endif // SENSORS_H
