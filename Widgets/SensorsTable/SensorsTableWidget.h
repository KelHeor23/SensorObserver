#ifndef SENSORSTABLEWIDGET_H
#define SENSORSTABLEWIDGET_H

#include <QtWidgets/QWidget>
#include <QHBoxLayout>

#include "DisplayingSensors.h"
#include "Exchange/Client.h"
#include "Exchange/Protocols/SensorsFrames.h"
#include "VibrationDirection.h"

class SensorsTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsTableWidget(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent = nullptr);

private:
    void engineSensorsVisual();
    void readEngineSensorsMsg(uint8_t num, const QByteArray& data);
    void readVoltageRegulatorsMsg(uint8_t num, const QByteArray& data);
    void readEscSensors(uint8_t num, uint16_t frame_id, const QByteArray& data);

public slots:
    void parseMsg(const QByteArray& data);

private:
    QHBoxLayout *mainHBoxLt;
    QWidget *placeholderWidget;
    std::shared_ptr<SensorsFrames> sensorsManager;
    QVector<VibrationDirection *> vibrationDirections;
    QVector<DisplayingSensors *> displayngSensors;

    Client *client;
};

#endif // SENSORSTABLEWIDGET_H
