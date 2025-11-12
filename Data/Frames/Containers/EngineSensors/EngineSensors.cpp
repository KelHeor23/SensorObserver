/**
 * \file EngineSensors.cpp
 * \brief Реализация парсера фрейма датчиков двигателя.
 * \details Извлекает runoutAngle/runoutAmplitude, обновляет поля и публикует.
 */

#include "EngineSensors.h"

#include "Tools/SaveToCSV.h"
#include "Data/DataStructure.h"

namespace EngineSensors {
/** \brief Инициализация: имя фрейма, порядок полей и создание записей в fields. */

EngineSensors::EngineSensors(){
    nameFrame = "Датчики двигателя";
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

void EngineSensors::setData(std::string_view data, int16_t node_id)
{
    if (data.size() < sizeof(EngineSensorsData)) {
        throw std::runtime_error("Insufficient data size");
    }

    auto receivedData = std::make_shared<EngineSensorsData>();
    memcpy(receivedData.get(), data.data(), sizeof(EngineSensorsData));
    /** \note Поля: «Угол биения» ← runoutAngle; «Амплитуда биения» ← runoutAmplitude. */

    fields["Угол биения"]->val      = static_cast<int>(receivedData->runoutAngle);
    fields["Амплитуда биения"]->val = static_cast<int>(receivedData->runoutAmplitude);

    UnifiedCsvWriter::Instance().addEngineData(receivedData);
    DataStructure::Instance().addData(node_id, nameFrame, ENGINE, receivedData);
}

}
