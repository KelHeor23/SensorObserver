#include "DisplayingSensors.h"

DisplayingSensors::DisplayingSensors(QWidget *parent)
    : QWidget(parent)
    ,mainLayout(new QGridLayout())
    ,sensorManager(std::make_unique<SensorsFrames>())
{
    setLayout(mainLayout);
    mainLayout->setColumnStretch(1, 1);  // Прогресс-бары будут растягиваться
    mainLayout->setColumnMinimumWidth(0, 150); // Фиксированная ширина для меток (опционально)
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setColumnMinimumWidth(1, 80);
}

void DisplayingSensors::addWidgets(std::string_view name)
{
    QLabel *labelName = new QLabel(QString::fromStdString(std::string(name)), this);

    ColorProgressBar *pb = new ColorProgressBar(this);
    sensorsColorProgressBarDataLabels[name.data()] = pb;

    // Получаем текущий индекс строки
    int row = mainLayout->rowCount();

    // Добавляем элементы в сетку
    mainLayout->addWidget(labelName, row, 0);          // Столбец 0: метка
    mainLayout->addWidget(pb, row, 1);                 // Столбец 1: прогресс-бар
    mainLayout->addItem(new QSpacerItem(20, 20), row, 2); // Столбец 2: отступ

    // Устанавливаем растяжение для последней строки (чтобы контент был прижат к верху)
    //mainLayout->setRowStretch(row + 1, 1);

    // Для выравнивания текста меток по правому краю
    labelName->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // Для установки фиксированной высоты строк
    mainLayout->setRowMinimumHeight(row, 20);
}

/*void DisplayingSensors::checkRangeValues(QLabel *lbl, std::shared_ptr<SensorData> field)
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
}*/

void DisplayingSensors::checkRangeValues(ColorProgressBar *pb, std::shared_ptr<SensorData> field){
    const int value = field->val;  // Кэшируем значение
    const auto& limits = *field->detalaizedLimits;  // Ссылка на вектор

    pb->setMinimum(field->limit->min);
    pb->setMaximum(field->limit->max);

    // 1. Проверка детализированных лимитов (если включены)
    if (field->settings->useDetalaizedLimits) {
        for (const auto& it : limits) {
            if (value >= it.limit.min && value <= it.limit.max) {
                pb->setColor(it.color);
                return;  // Выходим сразу после установки цвета
            }
        }
    }

    // 2. Проверка основных лимитов (только если min < max)
    const auto& main_limit = *field->limit;
    if (main_limit.min >= main_limit.max) {
        pb->setColor(Qt::transparent);
        return;
    }

    // Кэшируем вычисляемые значения
    const int range = main_limit.max - main_limit.min;
    const double threshold = 0.15 * range;
    const int low_threshold = main_limit.min + static_cast<int>(threshold);
    const int high_threshold = main_limit.max - static_cast<int>(threshold);

    // Определение цвета по основным лимитам
    if (value < main_limit.min || value > main_limit.max) {
        pb->setColor(Qt::red);
    }
    else if (value <= low_threshold || value >= high_threshold) {
        pb->setColor(Qt::yellow);
    }
    else {
        pb->setColor(Qt::green);
    }
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

void DisplayingSensors::setSensorsData(FrameTypes type, std::string_view data, int16_t node_id)
{
    auto& managerFrames = sensorManager->getFrames();
    managerFrames[type]->setData(data, node_id % 32);
    auto &fields = managerFrames[type]->getFields();

    for (auto &it : managerFrames[type]->orderedNames) {
        sensorsColorProgressBarDataLabels[it.data()]->setValue(fields[it.data()]->val);
        checkRangeValues(sensorsColorProgressBarDataLabels[it.data()], fields[it.data()]);
    }
}

void DisplayingSensors::addNewDataLabels(std::vector<SensorName> &list)
{
    for (auto &it : list)
        addWidgets(it);
}
