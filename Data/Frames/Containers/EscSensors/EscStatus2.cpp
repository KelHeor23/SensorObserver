/**
 * \file EscStatus2.cpp
 * \brief Реализация парсера для фрейма ESC Status2.
 * \details Заполняет Bus voltage/current и Motor line current; пишет CSV и публикует в DataStructure.
 */

#include "EscStatus2.h"

#include "Tools/SaveToCSV.h"
#include "Data/DataStructure.h"

EscSensors::EscStatus2::EscStatus2()
{
    nameFrame = "ESC Питание";
    orderedNames = sensorNamesFrame2;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}
/**
 * \brief Разбор входного кадра и публикация значений.
 * \details Вызывает соответствующий \c EscStatusInfoOtherSensorsData/EngineSensorsData::unpack,
 * заполняет поля, пишет строку в CSV и прокидывает кадр в DataStructure.*/

void EscSensors::EscStatus2::setData(std::string_view data, int16_t node_id)
{
    auto tempStatus2 = EscStatusInfo2::unpack(reinterpret_cast<const char*>(data.data()));
    /** \note Поля: Bus voltage ← voltage; Bus current ← bus_current; Motor line current ← current. */
    fields["Bus voltage"]->val = static_cast<double>(tempStatus2->voltage);
    fields["Bus current"]->val = static_cast<double>(tempStatus2->bus_current);
    fields["Motor line current"]->val = static_cast<double>(tempStatus2->current);

    UnifiedCsvWriter::Instance().addEscF2Data(node_id, tempStatus2);
    DataStructure::Instance().addData(node_id, nameFrame, ESC_FRAME2, tempStatus2);
}
