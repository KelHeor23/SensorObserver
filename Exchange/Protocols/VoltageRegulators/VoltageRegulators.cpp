#include "VoltageRegulators.h"
#include <cmath>


VoltageRegulators::VoltageRegulators::VoltageRegulators()
{

}

void VoltageRegulators::VoltageRegulators::setData(std::string_view data)
{
    if (data.size() < sizeof(VoltageRegulatorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    const VoltageRegulatorsData* receivedData = reinterpret_cast<const VoltageRegulatorsData*>(data.data());

    uint16_t intPart    = receivedData->inputVoltageHP | (receivedData->inputVoltageLP & 0xF);
    uint8_t  floatPart  = receivedData->inputVoltageLP & 0x0F;

    sensorsData["Входное напряжене"]            = static_cast<double>(intPart) + (floatPart * 0.1 + 0.01); //  !! Исправить
    sensorsData["ток (ампер)"]                  = static_cast<double>(receivedData->electricCurrent);
    sensorsData["Управляющий ШИМ"]              = static_cast<double>(receivedData->controlPWM);
    sensorsData["Среднее напряжение A"]         = static_cast<double>(receivedData->averageVoltageA);
    sensorsData["Среднее напряжение B"]         = static_cast<double>(receivedData->averageVoltageB);
    sensorsData["Среднее напряжение C"]         = static_cast<double>(receivedData->averageVoltageC);
}

std::unordered_map<SensorName, double> VoltageRegulators::VoltageRegulators::getSensorsData() const
{
    return sensorsData;
}
