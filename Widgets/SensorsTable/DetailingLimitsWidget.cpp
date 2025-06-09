#include "DetailingLimitsWidget.h"

#include <QLabel>
#include <QLineEdit>

#include "Tools/ColorButton.h"

DetailingLimitsWidget::DetailingLimitsWidget(SensorData &data, QWidget *parent)
    : QWidget{parent}
    , data_t(data)
    , mainLt(new QVBoxLayout(this))
    , fieldsLt(new QVBoxLayout(this))
    , buttonsLt(new QHBoxLayout(this))
    , addNewMinMaxBtn(new QPushButton("Добавить MinMax", this))
    , addNewPointBtn(new QPushButton("Добавить точку", this))
{
    buttonsLt->addWidget(addNewMinMaxBtn);
    buttonsLt->addWidget(addNewPointBtn);

    connect(addNewMinMaxBtn, &QPushButton::clicked, this, &DetailingLimitsWidget::addNewMinMax);
    connect(addNewPointBtn, &QPushButton::clicked, this, &DetailingLimitsWidget::addNewPoint);

    mainLt->addLayout(fieldsLt);
    mainLt->addLayout(buttonsLt);
    setLayout(mainLt);
}

void DetailingLimitsWidget::addNewMinMax()
{
    QHBoxLayout *tmpLt(new QHBoxLayout(this));

    tmpLt->setContentsMargins(0, 0, 0, 0);
    tmpLt->setSpacing(5);  // небольшой фиксированный отступ между элементами

    QLabel *lblMin(new QLabel("Min:", this));
    QLineEdit *minTxtEdt = new QLineEdit(this);
    QLabel *lblMax(new QLabel("Max:", this));
    QLineEdit *maxTxtEdt = new QLineEdit(this);
    ColorButton *colorBtn = new ColorButton(this);


    tmpLt->addWidget(lblMin);
    tmpLt->addWidget(minTxtEdt);
    tmpLt->addWidget(lblMax);
    tmpLt->addWidget(maxTxtEdt);
    tmpLt->addWidget(colorBtn);

    fieldsLt->addLayout(tmpLt);
}

void DetailingLimitsWidget::addNewPoint()
{
    QHBoxLayout *tmpLt(new QHBoxLayout(this));

    tmpLt->setContentsMargins(0, 0, 0, 0);
    tmpLt->setSpacing(5);  // небольшой фиксированный отступ между элементами

    QLabel *lblPoint(new QLabel("Point:", this));
    QLineEdit *pointTxtEdt = new QLineEdit(this);
    ColorButton *colorBtn = new ColorButton(this);

    tmpLt->addWidget(lblPoint);
    tmpLt->addWidget(pointTxtEdt);
    tmpLt->addWidget(colorBtn);

    fieldsLt->addLayout(tmpLt);
}
