/**
 * \file OtherSensors.h
 * \brief Интерфейс фрейма прочих датчиков.
 * \details Содержит реактивные моменты и тягу для двух двигателей.
 */

#ifndef OTHERSENSORS_H
#define OTHERSENSORS_H

#include <vector>

#include "Data/Frames/Containers/Base.h"
/** \brief Упорядоченный список имён сенсоров для отображения в UI/CSV. */

static std::vector<SensorName> sensorNames = {"Реакт. мом. двиг 1", "Реакт. мом. двиг 2", "Тяга 1", "Тяга 2"};
/** \namespace OtherSensors
 *  \brief Контейнеры прочих датчиков. */

namespace OtherSensors {
/**\class OtherSensors
 * \brief Контейнер и парсер фрейма OtherSensors.
 * \details Хранит имя фрейма, список полей и реализует разбор входных данных.
 */
class OtherSensors : public BaseProtocol
{
public:
    /** \brief Конструктор: задаёт имя фрейма и инициализирует поля значением 0. */
    OtherSensors();
    /** \brief Разбирает входные байты и обновляет поля/хранилище.
 *  \param[in] data Буфер данных кадра.
 *  \param[in] node_id Идентификатор узла/двигателя.
 */

    void setData(std::string_view data, int16_t node_id) override;
};
}
#endif // OTHERSENSORS_H

