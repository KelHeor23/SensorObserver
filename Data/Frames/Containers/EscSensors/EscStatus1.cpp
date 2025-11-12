/**
 * \file EscStatus1.cpp
 * \brief Реализация парсера для фрейма ESC Status1.
 * \details Заполняет поля RPM, recv_pwm, comm_pwm; пишет CSV и прокидывает кадр в DataStructure.
 */

#include "EscStatus1.h"
#include "Tools/SaveToCSV.h"
#include "Data/DataStructure.h"

EscSensors::EscStatus1::EscStatus1()
{
    nameFrame = "ESC Мотор";
    orderedNames = sensorNamesFrame1;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}
/**
 * \brief Разбор входного кадра и публикация значений.
 * \details Вызывает соответствующий \c EscStatusInfoOtherSensorsData/EngineSensorsData::unpack,
 * заполняет поля, пишет строку в CSV и прокидывает кадр в DataStructure.*/

void EscSensors::EscStatus1::setData(std::string_view data, int16_t node_id)
{
    auto tempStatus1 = EscStatusInfo1::unpack(reinterpret_cast<const char*>(data.data()));
    /** \note Поля: RPM motor speed ← speed; recv_pwm ← recv_pwm; comm_pwm ← comm_pwm. */
    fields["RPM motor speed"]->val = static_cast<double>(tempStatus1->speed);
    fields["recv_pwm"]->val = static_cast<double>(tempStatus1->recv_pwm);
    fields["comm_pwm"]->val = static_cast<double>(tempStatus1->comm_pwm);

    UnifiedCsvWriter::Instance().addEscF1Data(node_id, tempStatus1);
    DataStructure::Instance().addData(node_id, nameFrame, ESC_FRAME1, tempStatus1);
}
