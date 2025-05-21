#include "SensorsTableWidget.h"
#include <iostream>
#include <ostream>

#include "../../Common/Common.h"
#include "../../Exchange/Protocols/Constants.h"
#include "../../Exchange/Protocols/EngineSensors/EngineSensors.h"

SensorsTableWidget::SensorsTableWidget(QWidget *parent)
    : QWidget{parent},
    mainHBoxLt(new QHBoxLayout(this)),
    listOfLimits(new ListOfLimits(this)),
    placeholderWidget(new QWidget(this)),
    client(new Client(this))
{
    setLayout(mainHBoxLt);

    // Формир0уем визуализацию столбца приделов
    limitsVisual();

    for (int i = 0; i < 4; i++){
        vibrationDirections.append(new VibrationDirection(this));
    }

    for (int i = 0; i < 8; i++){
        displayngSensors.append(new DisplayingSensors(this));
        displayngSensors.last()->addNewDataLabels(EngineSensors::orderedNames);
        displayngSensors.last()->addNewDataLabels(VoltageRegulators::orderedNames);
        displayngSensors.last()->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    }

    // Формирование визуализации датчиков двигателей
    engineSensorsVisual();

    connect(client, SIGNAL(engineSensorsDataSent(QByteArray)), this, SLOT(parseMsg(QByteArray)));
}

void SensorsTableWidget::limitsVisual()
{
    QVBoxLayout *limitsVBox = new QVBoxLayout(this);
    limitsVBox->addWidget(placeholderWidget);
    limitsVBox->addWidget(listOfLimits);

    listOfLimits->addNewLimits(EngineSensors::orderedNames);
    listOfLimits->addNewLimits(VoltageRegulators::orderedNames);

    mainHBoxLt->addLayout(limitsVBox);

    placeholderWidget->setMinimumSize(170, 170);
    placeholderWidget->setMaximumSize(170, 170);
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

void SensorsTableWidget::parseMsg(const QByteArray& message)
{
    int it = 0;
    while (it + 4 < message.size()) { // первые четыре байта в каждом сообщении зарезервивона по дидентефикатор
        // Считываем первые 4 байта
        uint32_t value = (static_cast<uint32_t>(static_cast<unsigned char>(message[it])) << 24 |
                         static_cast<uint32_t>(static_cast<unsigned char>(message[it + 1])) << 16 |
                         static_cast<uint32_t>(static_cast<unsigned char>(message[it + 2])) << 8  |
                         static_cast<uint32_t>(static_cast<unsigned char>(message[it + 3])));

        value = swapEndianness(value);

        switch (value & ~0b111) {
        case Protocol_numbers::ENGINE_SENSORS:
            if (it + sizeof(EngineSensors::EngineSensorsData) > message.size())
            {
                qDebug() << "Ошибка чтения пакета данных";
                return;
            }
            readEngineSensorsMsg(value & 0b111, message.mid(it, sizeof(EngineSensors::EngineSensorsData)));
            it += sizeof(EngineSensors::EngineSensorsData);
            break;
        case Protocol_numbers::VOLTAGE_REGULATORS:
            if (it + sizeof(VoltageRegulators::VoltageRegulatorsData) > message.size())
            {
                qDebug() << "Ошибка чтения пакета данных";
                return;
            }
            readVoltageRegulatorsMsg(value & 0b111, message.mid(it, sizeof(VoltageRegulators::VoltageRegulatorsData)));
            it += sizeof(VoltageRegulators::VoltageRegulatorsData);
            break;
        default:
            qDebug() << "Ошибка чтения пакета данных";
            return;
        };
    }
}

void SensorsTableWidget::toggleLimitsVisibility()
{
    placeholderWidget->setVisible(!placeholderWidget->isVisible());
    listOfLimits->setVisible(!listOfLimits->isVisible());
}
