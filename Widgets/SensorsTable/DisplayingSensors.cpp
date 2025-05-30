#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent)
    ,mainLayout(new QVBoxLayout(this))
    ,sensorManager(std::make_unique<SensorsFrames>())
{
    setLayout(mainLayout);
    mainLayout->addStretch();
}

void DisplayingSensors::addWidgets(std::string_view name)
{
    QHBoxLayout *row = new QHBoxLayout(this);
    QLabel *labelVal = new QLabel("Значение", this);
    sensorsDataLabels[name.data()] = labelVal;
    labelVal->setMaximumHeight(30);
    QLabel *labelName = new QLabel(name.data(), this);
    labelVal->setMaximumHeight(30);
    labelVal->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    row->addWidget(labelName);
    row->addWidget(labelVal);

    row->addSpacerItem(new QSpacerItem(20, 29));

    mainLayout->insertLayout(mainLayout->count() - 1, row);
}

void DisplayingSensors::checkRangeValues(QLabel *lbl, int val, std::shared_ptr<SensorLimits> lim)
{
    QPalette palette = lbl->palette();
    if (lim->min < lim->max) {
        double threshold = 0.15 * (lim->max - lim->min);
        if (val < lim->min || val > lim->max)
            palette.setColor(QPalette::Window, Qt::red);
        else if (val <= lim->min + threshold || val >= lim->max - threshold) {
            palette.setColor(QPalette::Window, Qt::yellow);
        }
        else
            palette.setColor(QPalette::Window, Qt::transparent);
    }
    lbl->setPalette(palette);
    lbl->setAutoFillBackground(true); // Включаем перерисовку фона
}

SensorsFrames*DisplayingSensors::getSensorManager() const
{
    return sensorManager.get();
}

void DisplayingSensors::linkLimitsSensorsFrames(SensorsFrames& sensorFrame)
{
    auto& managerFrames = sensorManager->getFrames(); // Ссылка на оригинал
    auto& targetFrames = sensorFrame.getFrames();     // Ссылка на оригинал

    for (auto &it : managerFrames[ENGINE]->getFields()){
        it.second.linkLimits(targetFrames[ENGINE]->getFields()[it.first]);
    }
    for (auto &it : managerFrames[VOLTAGE_REGULATORS]->getFields()){
        it.second.linkLimits(targetFrames[VOLTAGE_REGULATORS]->getFields()[it.first]);
    }
    for (auto &it : managerFrames[ESC]->getFields()){
        it.second.linkLimits(targetFrames[ESC]->getFields()[it.first]);
    }
}

void DisplayingSensors::setEngineSensorsData(std::string_view data)
{
    auto& managerFrames = sensorManager->getFrames(); // Ссылка на оригинал
    managerFrames[ENGINE]->setData(data);
    auto fields = managerFrames[ENGINE]->getFields();

    for (auto &it : managerFrames[ENGINE]->orderedNames) {
        sensorsDataLabels[it.data()]->setText(QString::number(fields[it.data()].val, 'f', 1));
        checkRangeValues(sensorsDataLabels[it.data()], fields[it.data()].val, fields[it.data()].limit);
    }
}

void DisplayingSensors::setVoltageRegulatorsSensorsData(std::string_view data)
{
    auto& managerFrames = sensorManager->getFrames(); // Ссылка на оригинал
    managerFrames[VOLTAGE_REGULATORS]->setData(data);
    auto fields = managerFrames[VOLTAGE_REGULATORS]->getFields();

    for (auto &it : managerFrames[VOLTAGE_REGULATORS]->orderedNames) {
        sensorsDataLabels[it.data()]->setText(QString::number(fields[it.data()].val, 'f', 1));
        checkRangeValues(sensorsDataLabels[it.data()], fields[it.data()].val, fields[it.data()].limit);
    }
}

void DisplayingSensors::setEscSensors(uint16_t frame_id, std::string_view data)
{
    auto& managerFrames = sensorManager->getFrames(); // Ссылка на оригинал
    managerFrames[ESC]->setData(data);
    auto fields = managerFrames[ESC]->getFields();

    for (auto &it : managerFrames[ESC]->orderedNames) {
        sensorsDataLabels[it.data()]->setText(QString::number(fields[it.data()].val, 'f', 1));
        checkRangeValues(sensorsDataLabels[it.data()], fields[it.data()].val, fields[it.data()].limit);
    }
}

void DisplayingSensors::addNewDataLabels(std::vector<SensorName> &list)
{
    for (auto &it : list)
        addWidgets(it);
}
