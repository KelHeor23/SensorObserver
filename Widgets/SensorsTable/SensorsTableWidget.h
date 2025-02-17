#ifndef SENSORSTABLEWIDGET_H
#define SENSORSTABLEWIDGET_H

#include <QtWidgets/QWidget>

#include "ListOfLimits.h"
#include "DisplayingSensors.h"
#include "../../Exchange/Client.h"

class SensorsTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsTableWidget(QWidget *parent = nullptr);

    void fillSensorsEngines();

signals:

private:
    QHBoxLayout *hBoxLayout;
    ListOfLimits *listOfLimits;
    DisplayingSensors *sensorsEngine_1;
    DisplayingSensors *sensorsEngine_2;
    DisplayingSensors *sensorsEngine_3;
    DisplayingSensors *sensorsEngine_4;
    Client *client;

    QTimer *timer; // тестовая
};

#endif // SENSORSTABLEWIDGET_H
