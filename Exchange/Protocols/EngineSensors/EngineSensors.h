#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <vector>

#include "Exchange/Protocols/Base.h"

namespace EngineSensors {

static std::vector<SensorName> sensorNames = {"Угол биения", "Амплитуда биения"};

#pragma pack(push, 1) // Отключаем выравнивание
    struct EngineSensorsData {
        uint32_t    canID;              // 0x1FF1200-0x1FF1207 (Младший бит - номер двигателя)
        bool        isCustomSensros;    // Флаг о том, что данные пришли с не вшшитых датчиков в ESc
        uint16_t    runoutAngle;        // Угол биения относительно метки на двигателе (0-359), градусы
        uint16_t    runoutAmplitude;    // Амплитуда биения (0 - 65535), мили-g
    };
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

class EngineSensors : public BaseProtocol
{
public:
    EngineSensors();

    void setData(std::string_view data, int16_t node_id) override;
};
};



#endif // ENGINESENSORS_H
