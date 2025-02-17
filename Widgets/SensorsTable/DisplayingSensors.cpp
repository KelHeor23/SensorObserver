#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    engineSensors(new EngineSensors::EngineSensors),
    voltageRegulatorsSensors(new VoltageRegulators::VoltageRegulators)
{
    setLayout(mainLayout);
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
    QPalette palette = lbl->palette();
    if (lim.min < lim.max) {
        double threshold = 0.15 * (lim.max - lim.min);
        if (val < lim.min || val > lim.max)
            palette.setColor(QPalette::Window, Qt::red);
            //lbl->setStyleSheet("background-color:: red; }");
        else if (val <= lim.min + threshold || val >= lim.max - threshold) {
            //lbl->setStyleSheet("background-color:: yellow; }");
            palette.setColor(QPalette::Window, Qt::yellow);
        }
        else
            palette.setColor(QPalette::Window, Qt::transparent);
            //lbl->setStyleSheet("background: transparent;");
    }
    lbl->setPalette(palette);
    lbl->setAutoFillBackground(true); // Включаем перерисовку фона
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
