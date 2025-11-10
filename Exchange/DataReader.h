/**
 * \file DataReader.h
 * \brief Чтение и разбор входящих сообщений телеметрии.
 * \date 2025-11-07
 *
 * This file is part of the SensorObserver project.
 * \details Класс подписывается на события приёма данных от сети (Client) и
 * обновляет виджеты таблицы датчиков (SensorsTableWidget). Данные приходят в виде последовательности
 * TLV/пакетов, парсинг выполняется в слоте parseMsg().
 */

#ifndef DATAREADER_H
#define DATAREADER_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QObject>
#include <QByteArray>
#endif

class Client;
class SensorsTableWidget;

/**
 * \class DataReader
 * \brief Получает бинарные сообщения от Client и транслирует их в виджеты.
 * \ingroup Exchange
 */
class DataReader : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief Конструктор.
     * \param _client Источник сетевых сообщений (TCP-клиент).
     * \param _sensorsTableWdgt Виджет, принимающий разобранные данные датчиков.
     */
    DataReader(Client *_client, SensorsTableWidget *_sensorsTableWdgt);

public slots:
    /**
     * \brief Разбор входящего бинарного сообщения.
     * \param data Полный буфер с новыми байтами протокола.
     * \note Слот, подключённый к сигналу Client::engineSensorsDataSent().
     */
    void parseMsg(const QByteArray& data);

private:
    Client *client; ///< Активный TCP-клиент (источник данных).
    SensorsTableWidget  *sensorsTableWdgt; ///< Целевой виджет таблицы датчиков.
};

#endif // DATAREADER_H
