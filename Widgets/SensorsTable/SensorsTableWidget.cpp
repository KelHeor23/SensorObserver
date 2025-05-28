#include "SensorsTableWidget.h"
#include <iostream>
#include <ostream>

#include "../../Exchange/Protocols/EngineSensors/EngineSensors.h"

SensorsTableWidget::SensorsTableWidget(QWidget *parent)
    : QWidget{parent},
    mainHBoxLt(new QHBoxLayout(this)),
    placeholderWidget(new QWidget(this)),
    client(new Client(this))
{
    setLayout(mainHBoxLt);

    for (int i = 0; i < 4; i++){
        vibrationDirections.append(new VibrationDirection(this));
    }

    for (int i = 0; i < 8; i++){
        displayngSensors.append(new DisplayingSensors(this));
        displayngSensors.last()->addNewDataLabels(EngineSensors::orderedNames);
        displayngSensors.last()->addNewDataLabels(VoltageRegulators::orderedNames);
        displayngSensors.last()->addNewDataLabels(EscSensors::orderedNames);
    }

    // Формирование визуализации датчиков двигателей
    engineSensorsVisual();

    connect(client, SIGNAL(engineSensorsDataSent(QByteArray)), this, SLOT(parseMsg(QByteArray)));
}

void SensorsTableWidget::engineSensorsVisual()
{
    QVBoxLayout *engineVBoxLt;
    QHBoxLayout *engineSensorsHBLt;

    for (int i = 0; i < vibrationDirections.size(); i++){
        engineVBoxLt = new QVBoxLayout(this);
        engineSensorsHBLt = new QHBoxLayout(this);
        vibrationDirections[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        engineVBoxLt->addWidget(vibrationDirections[i]);
        engineSensorsHBLt->addWidget(displayngSensors[i * 2]);
        engineSensorsHBLt->addWidget(displayngSensors[i * 2 + 1]);
        engineVBoxLt->addLayout(engineSensorsHBLt);
        mainHBoxLt->addLayout(engineVBoxLt);
    }
}

void SensorsTableWidget::readEngineSensorsMsg(uint8_t num, const QByteArray &data)
{
    std::string_view sv(data.constData() , data.size());

    if (num >= 8)
    {
        std::cerr << "readVoltageRegulatorsMsg" << std::endl;
        return;
    }

    displayngSensors[num]->setEngineSensorsData(sv);

    if (num % 2 == 0) {
        vibrationDirections[num / 2]->update(displayngSensors[num]->getEngineSensors()->getSensorsData()["Амплитуда биения"] / 1000, displayngSensors[num]->getEngineSensors()->getSensorsData()["Угол биения"]);
    }
}

void SensorsTableWidget::readVoltageRegulatorsMsg(uint8_t num, const QByteArray &data)
{
    std::string_view sv(data.constData() , data.size());

    if (num >= 8)
    {
        std::cerr << "readVoltageRegulatorsMsg" << std::endl;
        return;
    }

    displayngSensors[num]->setVoltageRegulatorsSensorsData(sv);
}

void SensorsTableWidget::readEscSensors(uint8_t num, uint16_t frame_id, const QByteArray& data)
{
    std::string_view sv(data.constData() , data.size());

    if (num >= 8)
    {
        std::cerr << "readVoltageRegulatorsMsg" << std::endl;
        return;
    }

    displayngSensors[num]->setEscSensors(frame_id, sv);
}

#include <QtEndian>

void SensorsTableWidget::parseMsg(const QByteArray& message)
{
    int it = 0;

    int16_t node_id = qFromLittleEndian<uint16_t>(reinterpret_cast<const uchar*>(message.constData()));
    int16_t frame_id = qFromLittleEndian<uint16_t>(reinterpret_cast<const uchar*>(message.constData() + sizeof(uint16_t)));

    readEscSensors(node_id % 32, frame_id, message.mid(4));
}
