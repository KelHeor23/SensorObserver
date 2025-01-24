#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout)
{
    setLayout(mainLayout);

    // Добавление кнопки для добавления виджетов
    QPushButton *button = new QPushButton("Добавить виджеты");
    connect(button, &QPushButton::clicked, this, &DisplayingSensors::addWidgets);
    mainLayout->addWidget(button);
}

void DisplayingSensors::addWidgets()
{
    QHBoxLayout *row = new QHBoxLayout(this);;
    row->addWidget(new QLabel("Значение"));

    mainLayout->insertLayout(mainLayout->count() - 1, row);
}
