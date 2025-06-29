#include "VoltageRegulators.h"
#include "Tools/SaveToCSV.h"
#include <cmath>


VoltageRegulators::VoltageRegulators::VoltageRegulators()
{
    nameFrame = "Датчики питания";
    orderedNames = sensorNames;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}

void VoltageRegulators::VoltageRegulators::setData(std::string_view data, int16_t node_id)
{
    if (data.size() < sizeof(VoltageRegulatorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    const VoltageRegulatorsData* receivedData = reinterpret_cast<const VoltageRegulatorsData*>(data.data());

    uint16_t intPart    = receivedData->inputVoltageHP | (receivedData->inputVoltageLP & 0xF);
    uint8_t  floatPart  = receivedData->inputVoltageLP & 0x0F;

    fields["Входное напряжене"]->val            = static_cast<double>(intPart) + (floatPart * 0.1 + 0.01); //  !! Исправить
    fields["ток (ампер)"]->val                  = static_cast<double>(receivedData->electricCurrent);
    fields["Управляющий ШИМ"]->val              = static_cast<double>(receivedData->controlPWM);
    fields["Среднее напряжение A"]->val         = static_cast<double>(receivedData->averageVoltageA);
    fields["Среднее напряжение B"]->val         = static_cast<double>(receivedData->averageVoltageB);
    fields["Среднее напряжение C"]->val         = static_cast<double>(receivedData->averageVoltageC);

    UnifiedCsvWriter::Instance().addRegulatorData(*receivedData);
}
