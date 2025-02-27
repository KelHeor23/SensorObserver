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
    vibrationDirection_1(new VibrationDirection(this)),
    vibrationDirection_2(new VibrationDirection(this)),
    vibrationDirection_3(new VibrationDirection(this)),
    vibrationDirection_4(new VibrationDirection(this)),
    sensorsEngine_1(new DisplayingSensors(this)),
    sensorsEngine_2(new DisplayingSensors(this)),
    sensorsEngine_3(new DisplayingSensors(this)),
    sensorsEngine_4(new DisplayingSensors(this)),
    sensorsEngine_5(new DisplayingSensors(this)),
    sensorsEngine_6(new DisplayingSensors(this)),
    sensorsEngine_7(new DisplayingSensors(this)),
    sensorsEngine_8(new DisplayingSensors(this)),
    client(new Client(this))
{
    setLayout(mainHBoxLt);

    // Формир0уем визуализацию столбца приделов
    limitsVisual();

    // Формирование визуализации датчиков двигателей
    engineSensorsVisual();

    sensorsEngine_1->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_1->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_2->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_2->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_3->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_3->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_4->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_4->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_5->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_5->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_6->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_6->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_7->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_7->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_8->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_8->addNewDataLabels(VoltageRegulators::orderedNames);

    sensorsEngine_1->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_2->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_3->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_4->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_5->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_6->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_7->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_8->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());

    connect(client, SIGNAL(engineSensorsDataSent(QByteArray)), this, SLOT(parseMsg(QByteArray)));
}

void SensorsTableWidget::limitsVisual()
{
    // Создаем пустой виджет:
    QWidget *placeholderWidget = new QWidget(this);
    // Настраиваем политику размеров:
    //placeholderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //placeholderWidget->resize(vibrationDirection_1->size());


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
    QVBoxLayout *engineVBoxLt_1 = new QVBoxLayout(this);
    vibrationDirection_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    engineVBoxLt_1->addWidget(vibrationDirection_1);
    QHBoxLayout *engineSensorsHBLt = new QHBoxLayout(this);
    engineSensorsHBLt->addWidget(sensorsEngine_1);
    engineSensorsHBLt->addWidget(sensorsEngine_2);
    engineVBoxLt_1->addLayout(engineSensorsHBLt);
    mainHBoxLt->addLayout(engineVBoxLt_1);

    QVBoxLayout *engineVBoxLt_2 = new QVBoxLayout(this);
    vibrationDirection_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    engineVBoxLt_2->addWidget(vibrationDirection_2);
    engineSensorsHBLt = new QHBoxLayout(this);
    engineSensorsHBLt->addWidget(sensorsEngine_3);
    engineSensorsHBLt->addWidget(sensorsEngine_4);
    engineVBoxLt_2->addLayout(engineSensorsHBLt);
    mainHBoxLt->addLayout(engineVBoxLt_2);

    QVBoxLayout *engineVBoxLt_3 = new QVBoxLayout(this);
    vibrationDirection_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    engineVBoxLt_3->addWidget(vibrationDirection_3);
    engineSensorsHBLt = new QHBoxLayout(this);
    engineSensorsHBLt->addWidget(sensorsEngine_5);
    engineSensorsHBLt->addWidget(sensorsEngine_6);
    engineVBoxLt_3->addLayout(engineSensorsHBLt);
    mainHBoxLt->addLayout(engineVBoxLt_3);

    QVBoxLayout *engineVBoxLt_4 = new QVBoxLayout(this);
    vibrationDirection_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    engineVBoxLt_4->addWidget(vibrationDirection_4);
    engineSensorsHBLt = new QHBoxLayout(this);
    engineSensorsHBLt->addWidget(sensorsEngine_7);
    engineSensorsHBLt->addWidget(sensorsEngine_8);
    engineVBoxLt_4->addLayout(engineSensorsHBLt);
    mainHBoxLt->addLayout(engineVBoxLt_4);
}

void SensorsTableWidget::readEngineSensorsMsg(int num, const QByteArray &data)
{
    std::string_view sv(data.constData() , data.size());

    switch (num) {
    case 0:
        sensorsEngine_1->setEngineSensorsData(sv);
        vibrationDirection_1->update(sensorsEngine_1->getEngineSensors()->getSensorsData()["Амплитуда биения"] / 1000, sensorsEngine_1->getEngineSensors()->getSensorsData()["Угол биения"]);
        break;
    case 1: sensorsEngine_2->setEngineSensorsData(sv); break;
    case 2:
        sensorsEngine_3->setEngineSensorsData(sv);
        vibrationDirection_2->update(sensorsEngine_3->getEngineSensors()->getSensorsData()["Амплитуда биения"] / 1000, sensorsEngine_3->getEngineSensors()->getSensorsData()["Угол биения"]);
        break;
    case 3: sensorsEngine_4->setEngineSensorsData(sv); break;
    case 4:
        sensorsEngine_5->setEngineSensorsData(sv);
        vibrationDirection_3->update(sensorsEngine_5->getEngineSensors()->getSensorsData()["Амплитуда биения"] / 1000, sensorsEngine_5->getEngineSensors()->getSensorsData()["Угол биения"]);
        break;
    case 5: sensorsEngine_6->setEngineSensorsData(sv); break;
    case 6:
        sensorsEngine_7->setEngineSensorsData(sv);
        vibrationDirection_4->update(sensorsEngine_7->getEngineSensors()->getSensorsData()["Амплитуда биения"] / 1000, sensorsEngine_7->getEngineSensors()->getSensorsData()["Угол биения"]);
        break;
    case 7: sensorsEngine_8->setEngineSensorsData(sv); break;
    };
}

void SensorsTableWidget::parseMsg(const QByteArray& message)
{
    if (message.length() < 4) {
        // Обработка ошибки: данных недостаточно
        std::cerr << "Error: Not enough data." << std::endl;
        return;
    }

    int it = 0;
    while (it + 4 < message.size()) { // первые четыре байта в каждом сообщении зарезервивона по дидентефикатор
        // Считываем первые 4 байта
        uint32_t value = (static_cast<uint32_t>(static_cast<unsigned char>(message[0])) << 24 |
                         static_cast<uint32_t>(static_cast<unsigned char>(message[1])) << 16 |
                         static_cast<uint32_t>(static_cast<unsigned char>(message[2])) << 8  |
                         static_cast<uint32_t>(static_cast<unsigned char>(message[3])));

        value = swapEndianness(value);

        switch (value & ~0b111) {
        case Protocol_numbers::ENGINE_SENSORS:
            readEngineSensorsMsg(value & 0b111, message.mid(it, sizeof(EngineSensors::EngineSensorsData)));
            it += sizeof(EngineSensors::EngineSensorsData);
            break;
        case Protocol_numbers::VOLTAGE_REGULATORS:
            it += sizeof(VoltageRegulators::VoltageRegulatorsData);
            break;
        default:
            qDebug() << "Ошибка чтения пакета данных";
            return;
        };
    }
}
