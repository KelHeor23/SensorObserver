#ifndef DISPLAYINGSENSORS_H
#define DISPLAYINGSENSORS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "Exchange/Protocols/SensorsFrames.h"

class DisplayingSensors : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayingSensors(QWidget *parent = nullptr);

    void setSensorsData(FrameTypes type, std::string_view data);
    void addNewDataLabels(std::vector<SensorName> &list);

    SensorsFrames*getSensorManager() const;
    void linkLimitsSensorsFrames(SensorsFrames&);
    void linkFrame(FrameTypes type, SensorsFrames& target);

public slots:
    void addWidgets(std::string_view);
    void checkRangeValues(QLabel *, SensorData &filed);

private:    
    QVBoxLayout *mainLayout;
    std::unique_ptr<SensorsFrames> sensorManager;
    std::unordered_map<QString, QLabel *> sensorsDataLabels;
};

#endif // DISPLAYINGSENSORS_H
