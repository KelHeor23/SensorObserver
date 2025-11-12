/**
 * \file EscStatus3.h
 * \brief Интерфейс фрейма ESC: температуры и ошибки.
 * \details Контейнер EscStatus3: температура конденсатора/MCU/мотора, код ошибки.
 */

#ifndef ESCSTATUS3_H
#define ESCSTATUS3_H

#include "Data/Frames/Containers/Base.h"
/** \namespace EscSensors
 *  \brief Набор контейнеров статусов ESC. */

namespace EscSensors {
/** \brief Упорядоченный список имён сенсоров для отображения в UI/CSV. */

static std::vector<SensorName> sensorNamesFrame3 = {"cap_temp", "mcu_temp", "motor_temp", "Error"};
/**\class EscStatus3
 * \brief Контейнер и парсер фрейма EscStatus3.
 * \details Хранит имя фрейма, список полей и реализует разбор входных данных.
 */

class EscStatus3 : public BaseProtocol
{
public:
    /** \brief Конструктор: задаёт имя фрейма и инициализирует поля значением 0. */
    EscStatus3();
    /** \brief Разбирает входные байты и обновляет поля/хранилище.
 *  \param[in] data Буфер данных кадра.
 *  \param[in] node_id Идентификатор узла/двигателя.
 */
    void setData(std::string_view data, int16_t node_id) override;
};
}

#endif // ESCSTATUS3_H
