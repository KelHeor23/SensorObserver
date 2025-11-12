/**
 * \file VoltageRegulators.cpp
 * \brief Реализация протокола датчиков питания.
 * \details Разбирает пакет, обновляет поля для UI, пишет CSV и прокидывает данные в DataStructure.
 */

#include "VoltageRegulators.h"
#include "Tools/SaveToCSV.h"
#include "Data/DataStructure.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <cmath>
#endif
/**
 * \brief Инициализирует фрейм «Датчики питания» и регистрирует поля.
 * \details Выставляет \c nameFrame и \c orderedNames, создаёт записи в \c fields со значением 0.
 */

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

    auto receivedData = std::make_shared<VoltageRegulatorsData>();
    memcpy(receivedData.get(), data.data(), sizeof(VoltageRegulatorsData));

    fields["Среднее напряжение A"]->val         = static_cast<double>(receivedData->averageVoltageA);
    fields["Среднее напряжение B"]->val         = static_cast<double>(receivedData->averageVoltageB);
    fields["Среднее напряжение C"]->val         = static_cast<double>(receivedData->averageVoltageC);


    /** Запись строки в CSV и публикация кадра в глобальное хранилище. */
    UnifiedCsvWriter::Instance().addRegulatorData(receivedData);
    DataStructure::Instance().addData(node_id, nameFrame, VOLTAGE_REGULATORS, receivedData);
}
