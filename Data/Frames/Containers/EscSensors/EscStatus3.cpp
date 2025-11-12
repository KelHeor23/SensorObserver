/**
 * \file EscStatus3.cpp
 * \brief Реализация парсера для фрейма ESC Status3.
 * \details Заполняет cap_temp, mcu_temp, motor_temp, Error; пишет CSV и публикует в DataStructure.
 */

#include "EscStatus3.h"

#include "Tools/SaveToCSV.h"
#include "Data/DataStructure.h"

EscSensors::EscStatus3::EscStatus3()
{
    nameFrame = "ESC Температуры";
    orderedNames = sensorNamesFrame3;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}
/**
 * \brief Разбор входного кадра и публикация значений.
 * \details Вызывает соответствующий \c EscStatusInfo/OtherSensorsData/EngineSensorsData::unpack,
    * заполняет поля, пишет строку в CSV и прокидывает кадр в DataStructure.
                             */

void EscSensors::EscStatus3::setData(std::string_view data, int16_t node_id)
{
    auto tempStatus3 = EscStatusInfo3::unpack(reinterpret_cast<const char*>(data.data()));
    /** \note Поля: cap_temp, mcu_temp, motor_temp, Error. Значения берутся из EscStatusInfo3. */
    fields["cap_temp"]->val = static_cast<double>(tempStatus3->cap_temp);
    fields["mcu_temp"]->val = static_cast<double>(tempStatus3->mcu_temp);
    fields["motor_temp"]->val = static_cast<double>(tempStatus3->motor_temp);
    fields["Error"]->val = static_cast<double>(tempStatus3->Error);

    UnifiedCsvWriter::Instance().addEscF3Data(node_id, tempStatus3);
    DataStructure::Instance().addData(node_id, nameFrame, ESC_FRAME3, tempStatus3);
}
