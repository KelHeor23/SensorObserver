#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    sensors(new EngineSensors()),
    vibrationDirection(new VibrationDirection(*sensors, this))
{
    setLayout(mainLayout);
    mainLayout->addWidget(vibrationDirection);
    vibrationDirection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Добавление кнопки для добавления виджетов
    QPushButton *button = new QPushButton("Добавить виджеты");
    connect(button, &QPushButton::clicked, this, &DisplayingSensors::addWidgets);
    mainLayout->addWidget(button);
}

void DisplayingSensors::setEngineSensorsData(std::string_view data)
{
    sensors->setData(data);
}

void DisplayingSensors::addWidgets()
{
    QHBoxLayout *row = new QHBoxLayout(this);
    QLabel *label = new QLabel("Значение", this);
    label->setStyleSheet("background-color: yellow;");
    row->addWidget(label);

    mainLayout->insertLayout(mainLayout->count() - 1, row);
}
