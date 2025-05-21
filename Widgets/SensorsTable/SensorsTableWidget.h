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
    void readEngineSensorsMsg(uint8_t num, const QByteArray& data);
    void readVoltageRegulatorsMsg(uint8_t num, const QByteArray& data);    

public slots:
    void parseMsg(const QByteArray& data);
    void toggleLimitsVisibility();

private:
    QHBoxLayout *mainHBoxLt;
    QWidget *placeholderWidget;
    ListOfLimits *listOfLimits;

    QVector<VibrationDirection *> vibrationDirections;
    QVector<DisplayingSensors *> displayngSensors;

    Client *client;
};

#endif // SENSORSTABLEWIDGET_H
