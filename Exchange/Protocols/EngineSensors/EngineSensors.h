#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <vector>

#include "../Sensors.h"

class EngineSensors: public Sensors
{
    struct EngineSensorsData {
        uint32_t    canID;
        uint16_t    speed;              // Обороты двигателя (0 - 65535), обор/м
        int8_t      temperature;        // Температура двигателя (-128 ... +127), градусы/10
        uint16_t    runoutAngle;        // Угол биения относительно метки на двигателе (0-359), градусы
        uint16_t    runoutAmplitude;    // Амплитуда биения (0 - 65535), мили-g

        void parseEngineSensorsData(std::string_view data);
    };

public:
    EngineSensors();

    std::vector<NodeSensor> sensorsData;

    void setData(std::string_view data);
private:
    EngineSensorsData engineSensorsData;
};


#endif // ENGINESENSORS_H
