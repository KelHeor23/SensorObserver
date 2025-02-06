#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <vector>

#include "../Sensors.h"

namespace EngineSensors {

namespace {
std::vector<NameSensor> SensorsList = {
    NameSensor{0, "Обороты"},
    NameSensor{1, "Температура"},
    NameSensor{2, "Угол биения"},
    NameSensor{3, "Амплитуда биения"}
};
};

class Limits {
public:
    Limits();
    std::vector<SensorLimits> sensorsDataLimits;
};

class EngineSensors
{
    /*struct EngineSensorsData {
        uint32_t    canID;
        uint16_t    speed;              // Обороты двигателя (0 - 65535), обор/м
        int8_t      temperature;        // Температура двигателя (-128 ... +127), градусы/10
        uint16_t    runoutAngle;        // Угол биения относительно метки на двигателе (0-359), градусы
        uint16_t    runoutAmplitude;    // Амплитуда биения (0 - 65535), мили-g

        void parseEngineSensorsData(std::string_view data);
    };*/

public:
    EngineSensors();

    void setData(std::string_view data);

    void setSensorsDataLimits(std::vector<SensorLimits> *newSensorsDataLimits);

private:

    std::vector<SensorLimits> *sensorsDataLimits;
};
};



#endif // ENGINESENSORS_H
