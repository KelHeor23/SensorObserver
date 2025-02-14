#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
    hBoxLayout(new QHBoxLayout(this)),
    listOfLimits(new ListOfLimits(this)),
    sensorsEngine_1(new DisplayingSensors(this)),
    sensorsEngine_2(new DisplayingSensors(this)),
    sensorsEngine_3(new DisplayingSensors(this)),
    sensorsEngine_4(new DisplayingSensors(this)),
    client(new Client(this))
{
    QWidget *centralWidget = new QWidget((this)); // Создаем центральный виджет
    setCentralWidget(centralWidget); // Устанавливаем центральный виджет

    centralWidget->setLayout(hBoxLayout); // Применяем компоновку к центральному виджету

    hBoxLayout->addWidget(listOfLimits);
    hBoxLayout->addWidget(sensorsEngine_1);
    hBoxLayout->addWidget(sensorsEngine_2);
    hBoxLayout->addWidget(sensorsEngine_3);
    hBoxLayout->addWidget(sensorsEngine_4);

    listOfLimits->addNewLimits(EngineSensors::orderedNames);
    listOfLimits->addNewLimits(VoltageRegulators::orderedNames);

    sensorsEngine_1->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_2->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_3->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());
    sensorsEngine_4->setSensorsDataLimits(listOfLimits->getSensorsDataLimits());

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::fillSensorsEngines);
    timer->start(1000); // Запускаем таймер на интервал 5 секунд
}

void MainWindow::fillSensorsEngines()
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
}
