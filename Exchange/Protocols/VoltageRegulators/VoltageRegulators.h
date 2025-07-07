#ifndef VOLTAGEREGULATORS_H
#define VOLTAGEREGULATORS_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "Exchange/Protocols/Sensors.h"
#include "Exchange/Protocols/Base.h"

namespace VoltageRegulators {

static std::vector<SensorName> sensorNames = {"Среднее напряжение A", "Среднее напряжение B", "Среднее напряжение C"};

#pragma pack(push, 1) // Отключаем выравнивание
struct VoltageRegulatorsData{
    uint32_t    canID;              // 0x1FF1210-0x1FF1217 (Младший бит - номер регулятора))
    bool        isCustomSensros;    // Флаг о том, что данные пришли с не вшшитых датчиков в ESc
    uint8_t     averageVoltageA;    // Среднее напряжение на фазе A (0-255), вольты/10
    uint8_t     averageVoltageB;    // Среднее напряжение на фазе B (0-255), вольты/10
    uint8_t     averageVoltageC;    // Среднее напряжение на фазе C (0-255), вольты/10
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания



class VoltageRegulators : public BaseProtocol
{
public:
    VoltageRegulators();

    void setData(std::string_view data, int16_t node_id) override;
};

};


#endif // VOLTAGEREGULATORS_H
