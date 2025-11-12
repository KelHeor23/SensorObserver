/**
 * \file EscStatus2.h
 * \brief Интерфейс фрейма ESC: питание.
 * \details Контейнер EscStatus2: шина напряжения/тока, ток фазы мотора.
 */

#ifndef ESCSTATUS2_H
#define ESCSTATUS2_H

#include "Data/Frames/Containers/Base.h"
/** \namespace EscSensors
 *  \brief Набор контейнеров статусов ESC. */

namespace EscSensors {
/** \brief Упорядоченный список имён сенсоров для отображения в UI/CSV. */

static std::vector<SensorName> sensorNamesFrame2 = {"Bus voltage", "Bus current", "Motor line current"};
/**\class EscStatus2
 * \brief Контейнер и парсер фрейма EscStatus2.
 * \details Хранит имя фрейма, список полей и реализует разбор входных данных.
 */

class EscStatus2 : public BaseProtocol
{
public:
    /** \brief Конструктор: задаёт имя фрейма и инициализирует поля значением 0. */
    EscStatus2();
    /** \brief Разбирает входные байты и обновляет поля/хранилище.
 *  \param[in] data Буфер данных кадра.
 *  \param[in] node_id Идентификатор узла/двигателя.
 */
    void setData(std::string_view data, int16_t node_id) override;
};
}

#endif // ESCSTATUS2_H

