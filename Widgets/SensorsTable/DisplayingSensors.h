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

    void setEngineSensorsData(std::string_view data);
    void setVoltageRegulatorsSensorsData(std::string_view data);
    void setEscSensors(uint16_t frame_id, std::string_view data);
    void addNewDataLabels(std::vector<SensorName> &list);

    SensorsFrames*getSensorManager() const;
    void linkLimitsSensorsFrames(SensorsFrames&);

public slots:
    void addWidgets(std::string_view);
    void checkRangeValues(QLabel *, int val, std::shared_ptr<SensorLimits> lim);

private:    
    QVBoxLayout *mainLayout;
    std::unique_ptr<SensorsFrames> sensorManager;
    std::unordered_map<QString, QLabel *> sensorsDataLabels;
};

#endif // DISPLAYINGSENSORS_H
