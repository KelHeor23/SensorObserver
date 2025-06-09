#ifndef DETAILINGLIMITSWIDGET_H
#define DETAILINGLIMITSWIDGET_H

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Exchange/Protocols/Sensors.h"

class DetailingLimitsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetailingLimitsWidget(SensorData& data, QWidget *parent = nullptr);

    explicit DetailingLimitsWidget(QWidget *parent = nullptr) = delete;

public slots:
    void addNewMinMax();
    void addNewPoint();

signals:

private:
    SensorData& data_t;
    QVBoxLayout *mainLt;
    QVBoxLayout *fieldsLt;
    QHBoxLayout *buttonsLt;
    QPushButton *addNewMinMaxBtn;
    QPushButton *addNewPointBtn;
};

#endif // DETAILINGLIMITSWIDGET_H
