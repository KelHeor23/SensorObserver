#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    sensors(new EngineSensors::EngineSensors),
    vibrationDirection(new VibrationDirection(this))
{
    setLayout(mainLayout);

    // Сначала добавляем vibrationDirection
    mainLayout->addWidget(vibrationDirection);
    vibrationDirection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Затем добавляем остальные виджеты сенсоров
    for (auto &it : EngineSensors::orderedNames)
        addWidgets(it);

    mainLayout->addStretch();
}

void DisplayingSensors::setEngineSensorsData(std::string_view data)
{
    sensors->setData(data);

    sensorsDataLabels["Обороты"]->setText(QString::number(sensors->getSensorsData()["Обороты"]));
    checkRangeValues(sensorsDataLabels["Обороты"], sensors->getSensorsData()["Обороты"], sensors->getSensorsDataLimits()->sensorsDataLimits["Обороты"]);

    sensorsDataLabels["Температура"]->setText(QString::number(sensors->getSensorsData()["Температура"]));
    checkRangeValues(sensorsDataLabels["Температура"], sensors->getSensorsData()["Температура"], sensors->getSensorsDataLimits()->sensorsDataLimits["Температура"]);

    sensorsDataLabels["Угол биения"]->setText(QString::number(sensors->getSensorsData()["Угол биения"]));
    checkRangeValues(sensorsDataLabels["Угол биения"], sensors->getSensorsData()["Угол биения"], sensors->getSensorsDataLimits()->sensorsDataLimits["Угол биения"]);

    sensorsDataLabels["Амплитуда биения"]->setText(QString::number(sensors->getSensorsData()["Амплитуда биения"]));
    checkRangeValues(sensorsDataLabels["Амплитуда биения"], sensors->getSensorsData()["Амплитуда биения"], sensors->getSensorsDataLimits()->sensorsDataLimits["Амплитуда биения"]);

    vibrationDirection->update(sensors->getSensorsData()["Амплитуда биения"] / 1000, sensors->getSensorsData()["Угол биения"]);
}

void DisplayingSensors::setSensorsDataLimits(EngineSensors::Limits *newSensorsDataLimits)
{
    sensors->setSensorsDataLimits(newSensorsDataLimits);
}

void DisplayingSensors::addWidgets(std::string_view name)
{
    QHBoxLayout *row = new QHBoxLayout(this);
    QLabel *labelVal = new QLabel("Значение", this);
    sensorsDataLabels.insert(name.data(), labelVal);
    labelVal->setMaximumHeight(30);
    QLabel *labelName = new QLabel(name.data(), this);
    labelVal->setMaximumHeight(30);

    row->addWidget(labelName);
    row->addWidget(labelVal);
    mainLayout->insertLayout(mainLayout->count(), row);
}

void DisplayingSensors::checkRangeValues(QLabel *lbl, int val, SensorLimits lim)
{
    if (lim.min < lim.max && (val < lim.min || val > lim.max))
        lbl->setStyleSheet("QLabel { color: red; }");
    else
        lbl->setStyleSheet("background: transparent;");
}
