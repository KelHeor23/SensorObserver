/**
 * \file VoltageRegulators.h
 * \brief Протокол чтения датчиков питания (регуляторы напряжения).
 * \details Формирует фрейм «Датчики питания» и предоставляет интерфейс setData() для парсинга входного пакета.
 */

#ifndef VOLTAGEREGULATORS_H
#define VOLTAGEREGULATORS_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <cstdint>
#include <vector>
#endif

#include "Data/Frames/Containers/Base.h"
/** \namespace VoltageRegulators
 *  \brief Компоненты протокола датчиков питания.
 */

namespace VoltageRegulators {
/**
 * \brief Имена сенсоров для отображения: средние фазные напряжения.
 * \details Порядок соответствует столбцам в UI и CSV: A, B, C.
 */

static std::vector<SensorName> sensorNames = {"Среднее напряжение A", "Среднее напряжение B", "Среднее напряжение C"};
/**
 * \class VoltageRegulators
 * \brief Реализация протокола для фрейма «Датчики питания».
 * \details Парсит входной пакет и обновляет набор полей (средние напряжения фаз).
 */

class VoltageRegulators : public BaseProtocol
{
public:
    VoltageRegulators();
    /**
 * \brief Разбирает входные байты и публикует значения.
 * \param[in] data Сырые байты сообщения протокола.
 * \param[in] node_id Индекс/узел источника (двигатель/модуль).
 * \post Обновлены поля \c fields, написана строка в CSV и вызван DataStructure::addData().
 */

    void setData(std::string_view data, int16_t node_id) override;
};

};


#endif // VOLTAGEREGULATORS_H
