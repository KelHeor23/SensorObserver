#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <unordered_map>
#include <vector>

#include "../Sensors.h"

namespace EngineSensors {

namespace {
    std::vector<std::string> orderedNames = {"Обороты", "Температура", "Угол биения", "Амплитуда биения"};
};

#pragma pack(push, 1) // Отключаем выравнивание
    struct EngineSensorsData {
        uint32_t    canID;              // 0x1FF1200-0x1FF1207 (Младший бит - номер двигателя)
        uint16_t    speed;              // Обороты двигателя (0 - 65535), обор/м
        int8_t      temperature;        // Температура двигателя (-128 ... +127), градусы/10
        uint16_t    runoutAngle;        // Угол биения относительно метки на двигателе (0-359), градусы
        uint16_t    runoutAmplitude;    // Амплитуда биения (0 - 65535), мили-g
    };
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

class Limits {
public:
    Limits();

    std::unordered_map<std::string, SensorLimits> sensorsDataLimits;
};

class EngineSensors
{
public:
    EngineSensors();

    void setData(std::string_view data);

    void setSensorsDataLimits(Limits *newSensorsDataLimits);

    std::unordered_map<std::string, int> getSensorsData() const;

    Limits *getSensorsDataLimits() const;

private:
    Limits *sensorsDataLimits;
    std::unordered_map<std::string, int> sensorsData;
};
};



#endif // ENGINESENSORS_H
