#include "DetailingLimitsWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

#include "Tools/ColorButton.h"
#include "qdebug.h"

DetailingLimitsWidget::DetailingLimitsWidget(SensorData &data, std::string &name, QWidget *parent)
    : QWidget{parent}
    , data_t(data)
    , mainLt(new QVBoxLayout())
    , fieldsLt(new QVBoxLayout())
    , buttonsLt(new QHBoxLayout())
    , addNewMinMaxBtn(new QPushButton("Добавить MinMax", this))
    , addNewPointBtn(new QPushButton("Добавить точку", this))
{
    setWindowTitle(QString("Поле ") + QString(name.data()));
    buttonsLt->addWidget(addNewMinMaxBtn);
    buttonsLt->addWidget(addNewPointBtn);

    // Добавление новых элементов по индексу
    connect(addNewMinMaxBtn, &QPushButton::clicked, this, [this](){
        data_t.detalaizedLimits->push_back(SensorLimitsColored{{0, 0}, QColor(Qt::black)});
        addNewMinMax(data_t.detalaizedLimits->size() - 1); // Передаём индекс
    });

    connect(addNewPointBtn, &QPushButton::clicked, this, [this](){
        data_t.detalaizedLimits->push_back(SensorLimitsColored{{0, 0}, QColor(Qt::black)});
        addNewPoint(data_t.detalaizedLimits->size() - 1); // Передаём индекс
    });

    // Итерация по индексам
    for (size_t i = 0; i < data_t.detalaizedLimits->size(); ++i) {
        auto& it = (*data_t.detalaizedLimits)[i];
        if (it.limit.min == it.limit.max)
            addNewPoint(i); // Передаём индекс
        else
            addNewMinMax(i); // Передаём индекс
    }

    mainLt->addLayout(fieldsLt);
    mainLt->addLayout(buttonsLt);
    setLayout(mainLt);
}

void DetailingLimitsWidget::addNewMinMax(size_t index)
{
    QHBoxLayout *tmpLt = new QHBoxLayout();
    tmpLt->setContentsMargins(0, 0, 0, 0);
    tmpLt->setSpacing(5);

    auto& field = (*data_t.detalaizedLimits)[index]; // Доступ по индексу

    QLabel *lblMin = new QLabel("Min:", this);
    QLineEdit *minTxtEdt = new QLineEdit(this);
    minTxtEdt->setValidator(new QIntValidator);
    minTxtEdt->setText(QString::number(field.limit.min));

    QLabel *lblMax = new QLabel("Max:", this);
    QLineEdit *maxTxtEdt = new QLineEdit(this);
    maxTxtEdt->setValidator(new QIntValidator);
    maxTxtEdt->setText(QString::number(field.limit.max));

    ColorButton *colorBtn = new ColorButton(this);
    colorBtn->setColor(field.color);

    // Лямбда захватывает индекс, а не ссылку
    connect(minTxtEdt, &QLineEdit::textChanged, [this, index](const QString& text) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) (*data_t.detalaizedLimits)[index].limit.min = value;
    });

    connect(maxTxtEdt, &QLineEdit::textChanged, [this, index](const QString& text) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) (*data_t.detalaizedLimits)[index].limit.max = value;
    });

    connect(colorBtn, &ColorButton::colorChanged, [this, index](const QColor& color) {
        (*data_t.detalaizedLimits)[index].color = color;
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
    tmpLt->setContentsMargins(0, 0, 0, 0);
    tmpLt->setSpacing(5);

    auto& field = (*data_t.detalaizedLimits)[index]; // Доступ по индексу

    QLabel *lblPoint = new QLabel("Point:", this);
    QLineEdit *pointTxtEdt = new QLineEdit(this);
    pointTxtEdt->setText(QString::number(field.limit.min));

    ColorButton *colorBtn = new ColorButton(this);
    colorBtn->setColor(field.color);

    // Лямбда захватывает индекс
    connect(pointTxtEdt, &QLineEdit::textChanged, [this, index](const QString& text) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) {
            auto& limit = (*data_t.detalaizedLimits)[index].limit;
            limit.min = limit.max = value;
        }
    });

    connect(colorBtn, &ColorButton::colorChanged, [this, index](const QColor& color) {
        (*data_t.detalaizedLimits)[index].color = color;
    });

    tmpLt->addWidget(lblPoint);
    tmpLt->addWidget(pointTxtEdt);
    tmpLt->addWidget(colorBtn);

    fieldsLt->addLayout(tmpLt);
}
