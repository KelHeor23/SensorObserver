#include "DetailingLimitsWidget.h"

#include <QLabel>
#include <QLineEdit>

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

    connect(addNewMinMaxBtn, &QPushButton::clicked, this, [this](){
        data_t.detalaizedLimits->push_back(SensorLimitsColored{{0, 0}, QColor(Qt::black)});
        addNewMinMax(data_t.detalaizedLimits->back());
    });

    connect(addNewPointBtn, &QPushButton::clicked, this, [this](){
        data_t.detalaizedLimits->push_back(SensorLimitsColored{{0, 0}, QColor(Qt::black)});
        addNewPoint(data_t.detalaizedLimits->back());
    });

    for (auto &it : *data_t.detalaizedLimits){
        if (it.limit.min == it.limit.max)
            addNewPoint(it);
        else
            addNewMinMax(it);
    }

    mainLt->addLayout(fieldsLt);
    mainLt->addLayout(buttonsLt);
    setLayout(mainLt);
}

void DetailingLimitsWidget::addNewMinMax(SensorLimitsColored& field)
{
    QHBoxLayout *tmpLt(new QHBoxLayout());

    tmpLt->setContentsMargins(0, 0, 0, 0);
    tmpLt->setSpacing(5);  // небольшой фиксированный отступ между элементами

    QLabel *lblMin(new QLabel("Min:", this));
    QLineEdit *minTxtEdt = new QLineEdit(this);
    minTxtEdt->setText(QString::number(field.limit.min));
    QLabel *lblMax(new QLabel("Max:", this));
    QLineEdit *maxTxtEdt = new QLineEdit(this);
    maxTxtEdt->setText(QString::number(field.limit.max));
    ColorButton *colorBtn = new ColorButton(this);
    colorBtn->setColor(field.color);

    connect(minTxtEdt, &QLineEdit::textChanged, [this,  &field](const QString& text) {
        bool ok;
        double value = text.toDouble(&ok);
        field.limit.min = value;

    });

    connect(maxTxtEdt, &QLineEdit::textChanged, [this,  &field](const QString& text) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) field.limit.max = value;
    });

    connect(colorBtn, &ColorButton::colorChanged, [this, &field](const QColor& color) {
            field.color = color;
    });

    tmpLt->addWidget(lblMin);
    tmpLt->addWidget(minTxtEdt);
    tmpLt->addWidget(lblMax);
    tmpLt->addWidget(maxTxtEdt);
    tmpLt->addWidget(colorBtn);

    fieldsLt->addLayout(tmpLt);
}

void DetailingLimitsWidget::addNewPoint(SensorLimitsColored& field)
{
    QHBoxLayout *tmpLt(new QHBoxLayout());

    tmpLt->setContentsMargins(0, 0, 0, 0);
    tmpLt->setSpacing(5);  // небольшой фиксированный отступ между элементами

    QLabel *lblPoint(new QLabel("Point:", this));
    QLineEdit *pointTxtEdt = new QLineEdit(this);
    pointTxtEdt->setText(QString::number(field.limit.min));
    ColorButton *colorBtn = new ColorButton(this);
    colorBtn->setColor(field.color);

    connect(pointTxtEdt, &QLineEdit::textChanged, [this,  &field](const QString& text) {
        bool ok;
        double value = text.toDouble(&ok);
        if (ok) {
            field.limit.max = value;
            field.limit.min = value;
        }
    });

    connect(colorBtn, &ColorButton::colorChanged, [&field](const QColor& color){
        field.color = color;
    });

    tmpLt->addWidget(lblPoint);
    tmpLt->addWidget(pointTxtEdt);
    tmpLt->addWidget(colorBtn);

    fieldsLt->addLayout(tmpLt);
}
