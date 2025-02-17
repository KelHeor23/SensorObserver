#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    engineSensors(new EngineSensors::EngineSensors),
    voltageRegulatorsSensors(new VoltageRegulators::VoltageRegulators)
{
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 10, 0, 50);
    mainLayout->addStretch();
}

void DisplayingSensors::setEngineSensorsData(std::string_view data)
{
    engineSensors->setData(data);

    for (auto &it : EngineSensors::orderedNames) {
        sensorsDataLabels[it.data()]->setText(QString::number(engineSensors->getSensorsData()[it.data()]));
        checkRangeValues(sensorsDataLabels[it.data()], engineSensors->getSensorsData()[it.data()], (*sensorsDataLimits)[it.data()]);
    }

    //vibrationDirection->update(engineSensors->getSensorsData()["Амплитуда биения"] / 1000, engineSensors->getSensorsData()["Угол биения"]);
}

void DisplayingSensors::setVoltageRegulatorsSensorsData(std::string_view data)
{
    voltageRegulatorsSensors->setData(data);

    for (auto &it : VoltageRegulators::orderedNames) {
        sensorsDataLabels[it.data()]->setText(QString::number(voltageRegulatorsSensors->getSensorsData()[it.data()], 'f', 1));
        checkRangeValues(sensorsDataLabels[it.data()], voltageRegulatorsSensors->getSensorsData()[it.data()], (*sensorsDataLimits)[it.data()]);
    }
}

void DisplayingSensors::addWidgets(std::string_view name)
{
    QHBoxLayout *row = new QHBoxLayout(this);
    QLabel *labelVal = new QLabel("Значение", this);
    sensorsDataLabels.insert(name.data(), labelVal);
    labelVal->setMaximumHeight(30);
    QLabel *labelName = new QLabel(name.data(), this);
    labelVal->setMaximumHeight(30);
    labelVal->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    row->addWidget(labelName);
    row->addWidget(labelVal);

    row->addSpacerItem(new QSpacerItem(20, 29));

    mainLayout->insertLayout(mainLayout->count() - 1, row);
}

void DisplayingSensors::checkRangeValues(QLabel *lbl, int val, SensorLimits lim)
{
    if (lim.min < lim.max && (val < lim.min || val > lim.max))
        lbl->setStyleSheet("QLabel { color: red; }");
    else
        lbl->setStyleSheet("background: transparent;");
}

EngineSensors::EngineSensors *DisplayingSensors::getEngineSensors() const
{
    return engineSensors;
}

void DisplayingSensors::setSensorsDataLimits(const std::shared_ptr<HashLimits> &newSensorsDataLimits)
{
    sensorsDataLimits = newSensorsDataLimits;
}

void DisplayingSensors::addNewDataLabels(std::vector<SensorName> &list)
{
    for (auto &it : list)
        addWidgets(it);
}
