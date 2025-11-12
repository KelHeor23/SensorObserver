/**
 * \file Constants.h
 * \brief Константы номеров/идентификаторов протокола.
 * \details Определяет числовые идентификаторы групп телеметрии, используемые при маршрутизации кадров.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <cstdint>
#endif
/** \namespace Protocol_numbers
 *  \brief Числовые идентификаторы групп телеметрии для маршрутизации кадров.
 */

namespace Protocol_numbers {
const uint32_t ENGINE_SENSORS       = 0x1FF1200;    // Сенсоры двигателй //\< Сенсоры двигателя (ESC/мотор/привод)

const uint32_t VOLTAGE_REGULATORS   = 0x1FF1210;    // Параетры регуляторов //\< Параметры регуляторов питания

const uint32_t OTHER_SENSROS        = 0x1FF1220;    // Прочие датчики //\< Прочие датчики (опечатка в имени сохранена для совместимости)

};

#endif // CONSTANTS_H
