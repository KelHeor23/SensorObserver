#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <unordered_map>
#include <vector>

#include "Exchange/Protocols/Base.h"

namespace EngineSensors {

#pragma pack(push, 1) // Отключаем выравнивание
    struct EngineSensorsData {
        uint32_t    canID;              // 0x1FF1200-0x1FF1207 (Младший бит - номер двигателя)
        uint16_t    speed;              // Обороты двигателя (0 - 65535), обор/м
        int8_t      temperature;        // Температура двигателя (-128 ... +127), градусы/10
        uint16_t    runoutAngle;        // Угол биения относительно метки на двигателе (0-359), градусы
        uint16_t    runoutAmplitude;    // Амплитуда биения (0 - 65535), мили-g
    };
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

class EngineSensors : public BaseProtocol
{
public:
    EngineSensors();

    void setData(std::string_view data) override;
};
};



#endif // ENGINESENSORS_H
