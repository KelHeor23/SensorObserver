/**
 * \file DataReader.cpp
 * \brief Реализация парсинга входящих сообщений телеметрии.
 * \date 2025-11-07
 *
 * This file is part of the SensorObserver project.
 */
#include "DataReader.h"
#include "Client.h"
#include "Data/Frames/Containers/Constants.h"
#include "Widgets/SensorsTable/SensorsTableWidget.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QDataStream>
#include <QtEndian>
#endif

/// \brief Создаёт ридер и подключает сигнал клиента к слоту парсинга.
DataReader::DataReader(Client *_client, SensorsTableWidget *_sensorsTableWdgt)
    : client(_client)
    , sensorsTableWdgt(_sensorsTableWdgt)
{
    connect(client, SIGNAL(engineSensorsDataSent(QByteArray)), this, SLOT(parseMsg(QByteArray)));
}


/// \brief Выполняет пошаговый разбор TLV/потока и обновляет соответствующие виджеты.
/// \param message Буфер входящих данных.
void DataReader::parseMsg(const QByteArray& message)
{
    if (message.size() < 4) {
        qDebug() << "Слишком короткое сообщение";
        return;
    }

    const auto *base = reinterpret_cast<const uchar*>(message.constData());
    const quint16 node_id  = qFromLittleEndian<quint16>(base + 0);
    const quint16 frame_id = qFromLittleEndian<quint16>(base + sizeof(quint16));

    const QByteArray payloadAfterHeader = message.mid(4);

    switch (frame_id) {
    case 20022:
        if (node_id < 32 && sensorsTableWdgt->displayngSensors.size() > int(node_id % 32))
            sensorsTableWdgt->displayngSensors[node_id % 32]
                ->setSensorsData(ESC_FRAME1, payloadAfterHeader.toStdString(), node_id);
        break;
    case 20023:
        if (node_id < 32 && sensorsTableWdgt->displayngSensors.size() > int(node_id % 32))
            sensorsTableWdgt->displayngSensors[node_id % 32]
                ->setSensorsData(ESC_FRAME2, payloadAfterHeader.toStdString(), node_id);
        break;
    case 20024:
        if (node_id < 32 && sensorsTableWdgt->displayngSensors.size() > int(node_id % 32))
            sensorsTableWdgt->displayngSensors[node_id % 32]
                ->setSensorsData(ESC_FRAME3, payloadAfterHeader.toStdString(), node_id);
        break;
    default:
        break;
    }

    int it = 0;

    // Должно хватать хотя бы на тег (4 байта)
    while (it + 4 <= message.size()) {

        // Читаем тег как LE-uint32
        const quint32 tag = qFromLittleEndian<quint32>(
            reinterpret_cast<const uchar*>(message.constData() + it)
            );

        const quint32 type = (tag & ~0b111u);
        const quint32 idx  = (tag &  0b111u);

        auto ensureSpace = [&](qsizetype need) -> bool {
            if (it + need > message.size()) {
                qDebug() << "Ошибка чтения пакета данных (не хватает байт). type =" << type;
                return false;
            }
            return true;
        };

        switch (type) {
        case Protocol_numbers::ENGINE_SENSORS: {
            if (!ensureSpace(sizeof(EngineSensorsData))) return;
            const QByteArray chunk = message.mid(it, sizeof(EngineSensorsData));
            sensorsTableWdgt->readEngineSensorsMsg(idx, chunk);
            it += sizeof(EngineSensorsData);
            break;
        }
        case Protocol_numbers::VOLTAGE_REGULATORS: {
            if (!ensureSpace(sizeof(VoltageRegulatorsData))) return;
            const QByteArray chunk = message.mid(it, sizeof(VoltageRegulatorsData));
            sensorsTableWdgt->readVoltageRegulatorsMsg(idx, chunk);
            it += sizeof(VoltageRegulatorsData);
            break;
        }
        case Protocol_numbers::OTHER_SENSROS: { // если это действительно такое имя
            if (!ensureSpace(sizeof(OtherSensorsData))) return;
            const QByteArray chunk = message.mid(it, sizeof(OtherSensorsData));
            sensorsTableWdgt->readOtherSensorsMsg(idx, chunk);
            it += sizeof(OtherSensorsData);
            break;
        }
        default:
            qDebug() << "Неизвестный тип тега:" << type << " — прекращаю парсинг";
            return;
        }
    }
}
