#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
    hBoxLayout(new QHBoxLayout),
    listOfLimits(new ListOfLimits),
    client(new Client(this))
{
    QWidget *centralWidget = new QWidget; // Создаем центральный виджет
    setCentralWidget(centralWidget); // Устанавливаем центральный виджет

    centralWidget->setLayout(hBoxLayout); // Применяем компоновку к центральному виджету

    hBoxLayout->addWidget(listOfLimits);
}
