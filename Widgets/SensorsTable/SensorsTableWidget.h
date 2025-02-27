#ifndef SENSORSTABLEWIDGET_H
#define SENSORSTABLEWIDGET_H

#include <QtWidgets/QWidget>

#include "ListOfLimits.h"
#include "DisplayingSensors.h"
#include "../../Exchange/Client.h"
#include "VibrationDirection.h"

class SensorsTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsTableWidget(QWidget *parent = nullptr);

private:
    void limitsVisual();
    void engineSensorsVisual();
    void readEngineSensorsMsg(int num, const QByteArray& data);

public slots:
    void parseMsg(const QByteArray& data);

private:
    QHBoxLayout *mainHBoxLt;
    ListOfLimits *listOfLimits;
    VibrationDirection *vibrationDirection_1;
    VibrationDirection *vibrationDirection_2;
    VibrationDirection *vibrationDirection_3;
    VibrationDirection *vibrationDirection_4;

    DisplayingSensors *sensorsEngine_1;
    DisplayingSensors *sensorsEngine_2;
    DisplayingSensors *sensorsEngine_3;
    DisplayingSensors *sensorsEngine_4;
    DisplayingSensors *sensorsEngine_5;
    DisplayingSensors *sensorsEngine_6;
    DisplayingSensors *sensorsEngine_7;
    DisplayingSensors *sensorsEngine_8;

    Client *client;
};

#endif // SENSORSTABLEWIDGET_H
