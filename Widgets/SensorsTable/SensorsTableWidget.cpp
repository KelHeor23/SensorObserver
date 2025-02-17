#include "SensorsTableWidget.h"

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
