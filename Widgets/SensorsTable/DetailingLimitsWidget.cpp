#include "DetailingLimitsWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>  // Изменено на DoubleValidator
#include <QRandomGenerator>

#include "Tools/ColorButton.h"
#include "Exchange/Protocols/SensorSettingsManager.h"

DetailingLimitsWidget::DetailingLimitsWidget(std::shared_ptr<SensorData> data, QString name, QWidget *parent)
    : QWidget(parent)
    , data_t(data)
    , sensorName(name)
    , mainLt(new QVBoxLayout(this))  // Установка родителя для layout
    , fieldsLt(new QVBoxLayout())
    , buttonsLt(new QHBoxLayout())
    , addNewMinMaxBtn(new QPushButton("Добавить MinMax", this))
    , addNewPointBtn(new QPushButton("Добавить точку", this))
{
    setWindowTitle("Поле " + sensorName);
    buttonsLt->addWidget(addNewMinMaxBtn);
    buttonsLt->addWidget(addNewPointBtn);

    // Добавление новых элементов по индексу
    connect(addNewMinMaxBtn, &QPushButton::clicked, this, [this](){
        data_t->detalaizedLimits->push_back(SensorLimitsColored{{0, 0},
                                                                QColor::fromRgb(QRandomGenerator::global()->generate())});
        addNewMinMax(data_t->detalaizedLimits->size() - 1);
    });

    connect(addNewPointBtn, &QPushButton::clicked, this, [this](){
        data_t->detalaizedLimits->push_back(SensorLimitsColored{{0, 0},
                                                                QColor::fromRgb(QRandomGenerator::global()->generate())});
        addNewPoint(data_t->detalaizedLimits->size() - 1);
    });

    // Итерация по индексам
    for (size_t i = 0; i < data_t->detalaizedLimits->size(); ++i) {
        const auto& it = (*data_t->detalaizedLimits)[i];
        if (it.limit.min == it.limit.max)
            addNewPoint(i);
        else
            addNewMinMax(i);
    }

    mainLt->addLayout(fieldsLt);
    mainLt->addLayout(buttonsLt);
}

void DetailingLimitsWidget::addNewMinMax(size_t index)
{
    QHBoxLayout *tmpLt = new QHBoxLayout();
    tmpLt->setContentsMargins(5, 2, 5, 2);  // Улучшенные отступы
    tmpLt->setSpacing(5);

    auto& field = (*data_t->detalaizedLimits)[index];

    QLabel *lblMin = new QLabel("Min:", this);
    QLineEdit *minTxtEdt = new QLineEdit(this);
    minTxtEdt->setValidator(new QDoubleValidator(this));  // Для поддержки double
    minTxtEdt->setText(QString::number(field.limit.min));

    QLabel *lblMax = new QLabel("Max:", this);
    QLineEdit *maxTxtEdt = new QLineEdit(this);
    maxTxtEdt->setValidator(new QDoubleValidator(this));
    maxTxtEdt->setText(QString::number(field.limit.max));

    ColorButton *colorBtn = new ColorButton(this);
    colorBtn->setColor(field.color);

    // Безопасный захват по значению
    connect(minTxtEdt, &QLineEdit::textChanged,
            [this, index](const QString& text) {
                bool ok;
                double value = text.toDouble(&ok);
                if (ok) (*data_t->detalaizedLimits)[index].limit.min = value;
            });

    connect(maxTxtEdt, &QLineEdit::textChanged,
            [this, index](const QString& text) {
                bool ok;
                double value = text.toDouble(&ok);
                if (ok) (*data_t->detalaizedLimits)[index].limit.max = value;
            });

    connect(colorBtn, &ColorButton::colorChanged,
            [this, index](const QColor& color) {
                (*data_t->detalaizedLimits)[index].color = color;
            });

    tmpLt->addWidget(lblMin);
    tmpLt->addWidget(minTxtEdt);
    tmpLt->addWidget(lblMax);
    tmpLt->addWidget(maxTxtEdt);
    tmpLt->addWidget(colorBtn);

    fieldsLt->addLayout(tmpLt);
}

void DetailingLimitsWidget::addNewPoint(size_t index)
{
    QHBoxLayout *tmpLt = new QHBoxLayout();
    tmpLt->setContentsMargins(5, 2, 5, 2);  // Улучшенные отступы
    tmpLt->setSpacing(5);

    auto& field = (*data_t->detalaizedLimits)[index];

    QLabel *lblPoint = new QLabel("Point:", this);
    QLineEdit *pointTxtEdt = new QLineEdit(this);
    pointTxtEdt->setValidator(new QDoubleValidator(this));  // Для поддержки double
    pointTxtEdt->setText(QString::number(field.limit.min));

    ColorButton *colorBtn = new ColorButton(this);
    colorBtn->setColor(field.color);

    // Безопасный захват по значению
    connect(pointTxtEdt, &QLineEdit::textChanged,
            [this, index](const QString& text) {
                bool ok;
                double value = text.toDouble(&ok);
                if (ok) {
                    auto& limit = (*data_t->detalaizedLimits)[index].limit;
                    limit.min = limit.max = value;
                }
            });

    connect(colorBtn, &ColorButton::colorChanged,
            [this, index](const QColor& color) {
                (*data_t->detalaizedLimits)[index].color = color;
            });

    tmpLt->addWidget(lblPoint);
    tmpLt->addWidget(pointTxtEdt);
    tmpLt->addWidget(colorBtn);

    fieldsLt->addLayout(tmpLt);
}

void DetailingLimitsWidget::closeEvent(QCloseEvent *event)
{
    SensorSettingsManager::saveSensor(sensorName, data_t);
    QWidget::closeEvent(event);
}
