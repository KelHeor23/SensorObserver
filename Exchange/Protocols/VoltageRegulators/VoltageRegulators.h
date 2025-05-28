#ifndef VOLTAGEREGULATORS_H
#define VOLTAGEREGULATORS_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "Exchange/Protocols/Sensors.h"
#include "Exchange/Protocols/Base.h"

namespace VoltageRegulators {

namespace {
    std::vector<SensorName> orderedNames = {"Входное напряжене", "ток (ампер)", "Управляющий ШИМ", "Среднее напряжение A", "Среднее напряжение B", "Среднее напряжение C"};
};
#pragma pack(push, 1) // Отключаем выравнивание
struct VoltageRegulatorsData{
    uint32_t    canID;              // 0x1FF1210-0x1FF1217 (Младший бит - номер регулятора))
    uint8_t     inputVoltageHP;     // Входное напряжение (0-4095), старшая часть, вольт
    uint8_t     inputVoltageLP;     // Входное напряжение младшая часть, последние 4 бита - Входное напряжение (0-9), сотни мили-вольт
    uint8_t     electricCurrent;    // Ток (0 - 255), ампер
    uint16_t    controlPWM;         // Управляющий ШИМ, (0-2000), микро-секунды
    uint8_t     averageVoltageA;    // Среднее напряжение на фазе A (0-255), вольты/10
    uint8_t     averageVoltageB;    // Среднее напряжение на фазе B (0-255), вольты/10
    uint8_t     averageVoltageC;    // Среднее напряжение на фазе C (0-255), вольты/10
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания



class VoltageRegulators : public BaseProtocol
{
public:
    VoltageRegulators();

    void setData(std::string_view data);

    std::unordered_map<SensorName, double> getSensorsData() const;

private:
    std::unordered_map<SensorName, double> sensorsData;
};

};


#endif // VOLTAGEREGULATORS_H
