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
}
