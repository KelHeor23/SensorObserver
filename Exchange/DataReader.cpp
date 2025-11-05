#include "DataReader.h"
#include "Common/Common.h"
#include "Data/Frames/Containers/Constants.h"

#include <QtEndian>

DataReader::DataReader(Client *_client, SensorsTableWidget *_sensorsTableWdgt)
    : client(_client)
    , sensorsTableWdgt(_sensorsTableWdgt)
{
    connect(client, SIGNAL(engineSensorsDataSent(QByteArray)), this, SLOT(parseMsg(QByteArray)));
}



void DataReader::parseMsg(const QByteArray& message)
{
    int it = 0;

    int16_t node_id = qFromLittleEndian<uint16_t>(reinterpret_cast<const uchar*>(message.constData()));
    int16_t frame_id = qFromLittleEndian<uint16_t>(reinterpret_cast<const uchar*>(message.constData() + sizeof(uint16_t)));

    switch(frame_id){
    case 20022: {
        sensorsTableWdgt->displayngSensors[node_id % 32]->setSensorsData(ESC_FRAME1, message.mid(4).constData(), node_id);
        break;
    }
    case 20023: {
        sensorsTableWdgt->displayngSensors[node_id % 32]->setSensorsData(ESC_FRAME2, message.mid(4).constData(), node_id);
        break;
    }
    case 20024: {
        sensorsTableWdgt->displayngSensors[node_id % 32]->setSensorsData(ESC_FRAME3, message.mid(4).constData(), node_id);
        break;
    }
    default: break;
    }

    while (it + 4 < message.size()) { // первые четыре байта в каждом сообщении зарезервивона по дидентефикатор
        // Считываем первые 4 байта
        uint32_t value = (static_cast<uint32_t>(static_cast<unsigned char>(message[it])) << 24 |
                          static_cast<uint32_t>(static_cast<unsigned char>(message[it + 1])) << 16 |
                          static_cast<uint32_t>(static_cast<unsigned char>(message[it + 2])) << 8  |
                          static_cast<uint32_t>(static_cast<unsigned char>(message[it + 3])));

        value = swapEndianness(value);

        switch (value & ~0b111) {
        case Protocol_numbers::ENGINE_SENSORS:
            if (it + sizeof(EngineSensorsData) > message.size())
            {
                qDebug() << "Ошибка чтения пакета данных";
                return;
            }
            sensorsTableWdgt->readEngineSensorsMsg(value & 0b111, message.mid(it, sizeof(EngineSensorsData)));
            it += sizeof(EngineSensorsData);
            break;
        case Protocol_numbers::VOLTAGE_REGULATORS:
            if (it + sizeof(VoltageRegulatorsData) > message.size())
            {
                qDebug() << "Ошибка чтения пакета данных";
                return;
            }
            sensorsTableWdgt->readVoltageRegulatorsMsg(value & 0b111, message.mid(it, sizeof(VoltageRegulatorsData)));
            it += sizeof(VoltageRegulatorsData);
            break;
        case Protocol_numbers::OTHER_SENSROS:
            if (it + sizeof(OtherSensorsData) > message.size())
            {
                qDebug() << "Ошибка чтения пакета данных";
                return;
            }
            sensorsTableWdgt->readOtherSensorsMsg(value & 0b111, message.mid(it, sizeof(OtherSensorsData)));
            it += sizeof(OtherSensorsData);
            break;
        default:
            qDebug() << "Ошибка чтения пакета данных";
            return;
        };
    }
}
