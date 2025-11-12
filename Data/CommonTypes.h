/**
 * \file CommonTypes.h
 * \brief Общие типы-алиасы имён сенсоров и кадров.
 * \details Определяет строковые идентификаторы датчиков (SensorName) и фреймов (FrameName) для унификации ключей в структурах данных.
 */

#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <string>
#endif

/** \typedef SensorName
 *  \brief Строковый идентификатор конкретного сенсора.
 *  \details Используется как ключ в словарях DataStructure для доступа к временным рядам.
 */

using SensorName = std::string;
/** \typedef FrameName
 *  \brief Строковый идентификатор фрейма (группы родственных параметров).
 *  \details Например: "ESC", "Датчики питания", "ENGINE".
 */
using FrameName  = std::string;

#endif // COMMONTYPES_H
