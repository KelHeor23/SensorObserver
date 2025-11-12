/**
 * \file EscStatus1.h
 * \brief Интерфейс фрейма ESC: скорость мотора и PWM.
 * \details Определяет контейнер EscStatus1: RPM, полученный PWM и командный PWM.
 */

#ifndef ESCSTATUS1_H
#define ESCSTATUS1_H

#include "Data/Frames/Containers/Base.h"
/** \namespace EscSensors
 *  \brief Набор контейнеров статусов ESC. */

namespace EscSensors {
/** \brief Упорядоченный список имён сенсоров для отображения в UI/CSV. */

static std::vector<SensorName> sensorNamesFrame1 = {"RPM motor speed", "recv_pwm", "comm_pwm"};
/**\class EscStatus1
 * \brief Контейнер и парсер фрейма EscStatus1.
 * \details Хранит имя фрейма, список полей и реализует разбор входных данных.
 */

class EscStatus1 : public BaseProtocol
{
public:
    /** \brief Конструктор: задаёт имя фрейма и инициализирует поля значением 0. */
    EscStatus1();
    /** \brief Разбирает входные байты и обновляет поля/хранилище.
 *  \param[in] data Буфер данных кадра.
 *  \param[in] node_id Идентификатор узла/двигателя.
 */
    void setData(std::string_view data, int16_t node_id) override;
};
}


#endif // ESCSTATUS1_H

