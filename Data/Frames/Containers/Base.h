/**
 * \file Base.h
 * \brief Базовый интерфейс протокола фрейма.
 * \details Определяет общие поля (имя фрейма, упорядоченные имена сенсоров, словарь полей) и виртуальный метод setData().
 */

#ifndef BASE_H
#define BASE_H

#include "Sensors.h"
#include "Data/CommonTypes.h"

/**
 * \class BaseProtocol
 * \brief Базовый интерфейс контейнера фрейма сенсоров.
 * \details Содержит имя фрейма, упорядоченный список имён сенсоров и словарь полей.
 * Реализации должны переопределить setData() для разбора входного пакета.
 */

class BaseProtocol {

public:
    /** Возвращает константную ссылку на словарь полей (SensorName → SensorData). */
    const auto& getFields() const   { return fields; }
    /** Возвращает ссылку на словарь полей (SensorName → SensorData) для модификации. */
    auto& getFields()               { return fields; }

    /** \brief Разобрать сырые байты сообщения и обновить поля.
 *  \param[in] data Последовательность байтов.
 *  \param[in] node_id Идентификатор источника (двигатель/узел).
 */
    virtual void setData(std::string_view data, int16_t node_id) = 0;
public:
    /** Имя фрейма для UI/логов. */
    FrameName nameFrame;
    /** Упорядоченный список имён сенсоров (определяет порядок в UI/CSV). */
    std::vector<SensorName> orderedNames;
    /** Словарь полей фрейма: имя сенсора → данные и настройки. */
    std::unordered_map<SensorName, std::shared_ptr<SensorData>> fields;

    FrameName getNameFrame() const;
};
/** \return Имя фрейма, ассоциированное с контейнером. */

inline FrameName BaseProtocol::getNameFrame() const
{
    return nameFrame;
}

#endif // BASE_H
