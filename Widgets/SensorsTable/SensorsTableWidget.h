#ifndef SENSORSTABLEWIDGET_H
#define SENSORSTABLEWIDGET_H

#include <QtWidgets/QWidget>
#include <QHBoxLayout>

#include "DisplayingSensors.h"
#include "Data/Frames/Containers/SensorsFrames.h"
#include "VibrationDirection.h"

class SensorsTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsTableWidget(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent = nullptr);

    void readEngineSensorsMsg(uint8_t num, const QByteArray& data);
    void readVoltageRegulatorsMsg(uint8_t num, const QByteArray& data);
    void readOtherSensorsMsg(uint8_t num, const QByteArray& data);

private:
    void engineSensorsVisual();

public:
    QVector<DisplayingSensors *> displayngSensors;

private:
    QHBoxLayout *mainHBoxLt;
    QWidget *placeholderWidget;
    std::shared_ptr<SensorsFrames> sensorsManager;
    QVector<VibrationDirection *> vibrationDirections;    
};

#endif // SENSORSTABLEWIDGET_H
