#include "SensorsTableWidget.h"

SensorsTableWidget::SensorsTableWidget(QWidget *parent)
    : QWidget{parent},
    hBoxLayout(new QHBoxLayout(this)),
    listOfLimits(new ListOfLimits(this)),
    sensorsEngine_1(new DisplayingSensors(this)),
    sensorsEngine_2(new DisplayingSensors(this)),
    sensorsEngine_3(new DisplayingSensors(this)),
    sensorsEngine_4(new DisplayingSensors(this)),
    client(new Client(this))
{
    setLayout(hBoxLayout);

    hBoxLayout->addWidget(listOfLimits);
    hBoxLayout->addWidget(sensorsEngine_1);
    hBoxLayout->addWidget(sensorsEngine_2);
    hBoxLayout->addWidget(sensorsEngine_3);
    hBoxLayout->addWidget(sensorsEngine_4);

    listOfLimits->addNewLimits(EngineSensors::orderedNames);
    listOfLimits->addNewLimits(VoltageRegulators::orderedNames);

    sensorsEngine_1->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_1->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_2->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_2->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_3->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_3->addNewDataLabels(VoltageRegulators::orderedNames);
    sensorsEngine_4->addNewDataLabels(EngineSensors::orderedNames);
    sensorsEngine_4->addNewDataLabels(VoltageRegulators::orderedNames);

    sensorsEngine_1->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_2->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_3->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_4->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SensorsTableWidget::fillSensorsEngines);
    timer->start(1000); // Запускаем таймер на интервал 5 секунд
}

void SensorsTableWidget::fillSensorsEngines()
{
    EngineSensors::EngineSensorsData data;

    data.canID = 1;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    std::string str(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_1->setEngineSensorsData(str);

    data.canID = 2;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    str = std::string(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_2->setEngineSensorsData(str);

    data.canID = 3;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    str = std::string(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_3->setEngineSensorsData(str);

    data.canID = 4;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    str = std::string(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_4->setEngineSensorsData(str);

    VoltageRegulators::VoltageRegulatorsData dataVolt;

    dataVolt.inputVoltageHP = 0xFF;     // Входное напряжение (0-4095), старшая часть, вольт
    dataVolt.inputVoltageLP = 0x00000001;     // Входное напряжение младшая часть, последние 4 бита - Входное напряжение (0-9), сотни мили-вольт
    dataVolt.electricCurrent = 100;    // Ток (0 - 255), ампер
    dataVolt.controlPWM = 101;         // Управляющий ШИМ, (0-2000), микро-секунды
    dataVolt.averageVoltageA = 1;    // Среднее напряжение на фазе A (0-255), вольты/10
    dataVolt.averageVoltageB = 1;    // Среднее напряжение на фазе B (0-255), вольты/10
    dataVolt.averageVoltageC = 1;    // Среднее напряжение на фазе C (0-255), вольты/10

    str = std::string(reinterpret_cast<char *> (&dataVolt), sizeof(dataVolt));

    sensorsEngine_1->setVoltageRegulatorsSensorsData(str);
}
