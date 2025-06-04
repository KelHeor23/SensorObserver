#include "DetailingLimitsWidget.h"

DetailingLimitsWidget::DetailingLimitsWidget(SensorData &data, QWidget *parent)
    : QWidget{parent}
    , data_t(data)
    , mainLt(new QVBoxLayout(this))
    , buttonsLt(new QHBoxLayout(this))
    , addNewMinMaxBtn(new QPushButton("Добавить MinMax", this))
    , addNewPointBtn(new QPushButton("Добавить точку", this))
{
    buttonsLt->addWidget(addNewMinMaxBtn);
    buttonsLt->addWidget(addNewPointBtn);

    mainLt->addLayout(buttonsLt);
    setLayout(mainLt);
}

void DetailingLimitsWidget::addNewMinMax()
{

}

void DetailingLimitsWidget::addNewPoint()
{

}
