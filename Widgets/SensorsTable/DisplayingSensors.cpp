#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    sensorsEngine(new EngineSensors::EngineSensors),
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
    sensorsEngine->setData(data);

    for (auto &it : EngineSensors::orderedNames) {
        sensorsDataLabels[it.data()]->setText(QString::number(sensorsEngine->getSensorsData()[it.data()]));
        checkRangeValues(sensorsDataLabels[it.data()], sensorsEngine->getSensorsData()[it.data()], (*sensorsDataLimits)[it.data()]);
    }

    vibrationDirection->update(sensorsEngine->getSensorsData()["Амплитуда биения"] / 1000, sensorsEngine->getSensorsData()["Угол биения"]);
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

void DisplayingSensors::setSensorsDataLimits(const std::shared_ptr<HashLimits> &newSensorsDataLimits)
{
    sensorsDataLimits = newSensorsDataLimits;
}
