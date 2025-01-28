#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
    engineSensors(new EngineSensors),
    hBoxLayout(new QHBoxLayout(this)),
    listOfLimits(new ListOfLimits(*engineSensors, this)),
    sensorsEngine_1(new DisplayingSensors(*engineSensors, this)),
    sensorsEngine_2(new DisplayingSensors(*engineSensors, this)),
    sensorsEngine_3(new DisplayingSensors(*engineSensors, this)),
    sensorsEngine_4(new DisplayingSensors(*engineSensors, this)),
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
}
