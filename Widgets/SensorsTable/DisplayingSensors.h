#ifndef DISPLAYINGSENSORS_H
#define DISPLAYINGSENSORS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "VibrationDirection.h"
#include "../../Exchange/Protocols/EngineSensors/EngineSensors.h"

class DisplayingSensors : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayingSensors(QWidget *parent = nullptr);

    void setEngineSensorsData(std::string_view data);
    void setSensorsDataLimits(EngineSensors::Limits *newSensorsDataLimits);

public slots:
    void addWidgets(QString &);
    void checkRangeValues(QLabel *, int val, SensorLimits lim);

private:    
    QVBoxLayout *mainLayout;
    EngineSensors::EngineSensors *sensors;
    VibrationDirection *vibrationDirection;
    QMap<QString, QLabel *> sensorsData;
};

#endif // DISPLAYINGSENSORS_H
