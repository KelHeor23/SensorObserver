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
    /*for (auto &it : sensors->getSensorsDataLimits()->sensorsDataLimits)
        addWidgets(it.name.name);
*/
    mainLayout->addStretch();
}

void DisplayingSensors::setEngineSensorsData(std::string_view data)
{
    sensors->setData(data);

    /*sensorsData["Обороты"]->setText(QString::number(sensors->getSensorsData().speed));
    checkRangeValues(sensorsData["Обороты"], sensors->getSensorsData().speed, sensors->getSensorsDataLimits()->sensorsDataLimits[0]);

    sensorsData["Температура"]->setText(QString::number(sensors->getSensorsData().temperature));
    checkRangeValues(sensorsData["Температура"], sensors->getSensorsData().temperature, sensors->getSensorsDataLimits()->sensorsDataLimits[1]);

    sensorsData["Угол биения"]->setText(QString::number(sensors->getSensorsData().runoutAngle));
    checkRangeValues(sensorsData["Угол биения"], sensors->getSensorsData().runoutAngle, sensors->getSensorsDataLimits()->sensorsDataLimits[2]);

    sensorsData["Амплитуда биения"]->setText(QString::number(sensors->getSensorsData().runoutAmplitude));
    checkRangeValues(sensorsData["Амплитуда биения"], sensors->getSensorsData().runoutAmplitude, sensors->getSensorsDataLimits()->sensorsDataLimits[3]);

    vibrationDirection->update(sensors->getSensorsData().runoutAmplitude / 1000, sensors->getSensorsData().runoutAngle);*/
}

void DisplayingSensors::setSensorsDataLimits(EngineSensors::Limits *newSensorsDataLimits)
{
    sensors->setSensorsDataLimits(newSensorsDataLimits);
}

void DisplayingSensors::addWidgets(QString &name)
{
    QHBoxLayout *row = new QHBoxLayout(this);
    QLabel *labelVal = new QLabel("Значение", this);
    sensorsData.insert(name, labelVal);
    labelVal->setMaximumHeight(30);
    QLabel *labelName = new QLabel(name, this);
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
