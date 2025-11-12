/**
 * \file EngineSensors.h
 * \brief Интерфейс фрейма датчиков двигателя.
 * \details Содержит параметры биения: угол и амплитуда.
 */

#ifndef ENGINESENSORS_H
#define ENGINESENSORS_H

#include <vector>

#include "Data/Frames/Containers/Base.h"
/** \namespace EngineSensors
 *  \brief Контейнеры датчиков двигателя. */

namespace EngineSensors {
/** \brief Упорядоченный список имён сенсоров для отображения в UI/CSV. */

static std::vector<SensorName> sensorNames = {"Угол биения", "Амплитуда биения"};
/**\class EngineSensors
 * \brief Контейнер и парсер фрейма EngineSensors.
 * \details Хранит имя фрейма, список полей и реализует разбор входных данных.
 */

class EngineSensors : public BaseProtocol
{
public:
    /** \brief Конструктор: задаёт имя фрейма и инициализирует поля значением 0. */
    EngineSensors();
    /** \brief Разбирает входные байты и обновляет поля/хранилище.
 *  \param[in] data Буфер данных кадра.
 *  \param[in] node_id Идентификатор узла/двигателя.
 */

    void setData(std::string_view data, int16_t node_id) override;
};
};



#endif // ENGINESENSORS_H
