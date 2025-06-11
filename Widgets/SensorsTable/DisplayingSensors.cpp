#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent)
    ,mainLayout(new QVBoxLayout())
    ,sensorManager(std::make_unique<SensorsFrames>())
{
    setLayout(mainLayout);
    mainLayout->addStretch();
}

void DisplayingSensors::addWidgets(std::string_view name)
{
    QHBoxLayout *row = new QHBoxLayout();
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

void DisplayingSensors::checkRangeValues(QLabel *lbl, std::shared_ptr<SensorData> field)
{
    QPalette palette = lbl->palette();
    if (field->limit->min < field->limit->max) {
        double threshold = 0.15 * (field->limit->max - field->limit->min);
        if (field->val < field->limit->min || field->val > field->limit->max)
            palette.setColor(QPalette::Window, Qt::red);
        else if (field->val <= field->limit->min + threshold || field->val >= field->limit->max - threshold) {
            palette.setColor(QPalette::Window, Qt::yellow);
        }
        else
            palette.setColor(QPalette::Window, Qt::transparent);
    }
    if (field->useDetalaizedLimits) {
        for (auto &it : *field->detalaizedLimits) {
            if (field->val >= it.limit.min && field->val <= it.limit.max)
               palette.setColor(QPalette::Window, it.color);
        }
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
    linkFrame(ENGINE, sensorFrame);
    linkFrame(VOLTAGE_REGULATORS, sensorFrame);
    linkFrame(ESC_FRAME1, sensorFrame);
    linkFrame(ESC_FRAME2, sensorFrame);
    linkFrame(ESC_FRAME3, sensorFrame);
}

void DisplayingSensors::linkFrame(FrameTypes type, SensorsFrames &target)
{
    auto& srcFrame = sensorManager->getFrames()[type];
    auto& dstFrame = target.getFrames()[type];

    if (!srcFrame || !dstFrame) return;

    for (auto& [name, data] : srcFrame->getFields()) {
        if (auto it = dstFrame->getFields().find(name); it != dstFrame->getFields().end()) {
            data->linkLimits(it->second);
        }
    }
}

void DisplayingSensors::setSensorsData(FrameTypes type, std::string_view data)
{
    auto& managerFrames = sensorManager->getFrames();
    managerFrames[type]->setData(data);
    auto fields = managerFrames[type]->getFields();

    for (auto &it : managerFrames[type]->orderedNames) {
        sensorsDataLabels[it.data()]->setText(QString::number(fields[it.data()]->val, 'f', 1));
        checkRangeValues(sensorsDataLabels[it.data()], fields[it.data()]);
    }
}

void DisplayingSensors::addNewDataLabels(std::vector<SensorName> &list)
{
    for (auto &it : list)
        addWidgets(it);
}
