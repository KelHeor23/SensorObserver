/**
 * \file OtherSensors.cpp
 * \brief Реализация парсера фрейма прочих датчиков.
 * \details Извлекает reactiveTorque/thrust по двум каналам, пишет CSV и публикует.
 */

#include "OtherSensors.h"

#include "Tools/SaveToCSV.h"
#include "Data/DataStructure.h"

namespace OtherSensors {
/** \brief Инициализация: имя фрейма, порядок полей и создание записей в fields. */

OtherSensors::OtherSensors() {
    nameFrame = "Остальные датчики";
    orderedNames = sensorNames;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}

/**
 * \brief Разбор входного кадра и публикация значений.
 * \details Вызывает соответствующий \c EscStatusInfo/OtherSensorsData/EngineSensorsData::unpack,
 * заполняет поля, пишет строку в CSV и прокидывает кадр в DataStructure.*/

void OtherSensors::setData(std::string_view data, int16_t node_id)
{
    if (data.size() < sizeof(OtherSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    auto receivedData = std::make_shared<OtherSensorsData>();
    memcpy(receivedData.get(), data.data(), sizeof(OtherSensorsData));
    /** \note Поля: «Реакт. мом. двиг 1/2», «Тяга 1/2» — из OtherSensorsData. */

    fields["Реакт. мом. двиг 1"]->val = static_cast<double>(receivedData->reactiveTorquEngine1);
    fields["Реакт. мом. двиг 2"]->val = static_cast<double>(receivedData->reactiveTorquEngine2);
    fields["Тяга 1"]->val = static_cast<double>(receivedData->thrustEngine1);
    fields["Тяга 2"]->val = static_cast<double>(receivedData->thrustEngine2);

    UnifiedCsvWriter::Instance().addOtherSensorsData(receivedData);
    DataStructure::Instance().addData(node_id, nameFrame, OTHER_SENSROS, receivedData);
}
}
