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
    const int value = field->val;  // Кэшируем значение
    const auto& limits = *field->detalaizedLimits;  // Ссылка на вектор

    // 1. Проверка детализированных лимитов (если включены)
    if (field->settings->useDetalaizedLimits) {
        for (const auto& it : limits) {
            if (value >= it.limit.min && value <= it.limit.max) {
                palette.setColor(QPalette::Window, it.color);
                lbl->setPalette(palette);
                lbl->setAutoFillBackground(true);
                return;  // Выходим сразу после установки цвета
            }
        }
    }

    // 2. Проверка основных лимитов (только если min < max)
    const auto& main_limit = *field->limit;
    if (main_limit.min >= main_limit.max) {
        lbl->setAutoFillBackground(false);
        return;
    }

    // Кэшируем вычисляемые значения
    const int range = main_limit.max - main_limit.min;
    const double threshold = 0.15 * range;
    const int low_threshold = main_limit.min + static_cast<int>(threshold);
    const int high_threshold = main_limit.max - static_cast<int>(threshold);

    // Определение цвета по основным лимитам
    if (value < main_limit.min || value > main_limit.max) {
        palette.setColor(QPalette::Window, Qt::red);
    }
    else if (value <= low_threshold || value >= high_threshold) {
        palette.setColor(QPalette::Window, Qt::yellow);
    }
    else {
        palette.setColor(QPalette::Window, Qt::transparent);
    }

    lbl->setPalette(palette);
    lbl->setAutoFillBackground(true);
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
            data->linksSensorData(it->second);
        }
    }
}

void DisplayingSensors::setSensorsData(FrameTypes type, std::string_view data)
{
    auto& managerFrames = sensorManager->getFrames();
    managerFrames[type]->setData(data);
    auto &fields = managerFrames[type]->getFields();

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
