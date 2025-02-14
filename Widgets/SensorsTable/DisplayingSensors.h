#ifndef DISPLAYINGSENSORS_H
#define DISPLAYINGSENSORS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "ListOfLimits.h"
#include "VibrationDirection.h"
#include "../../Exchange/Protocols/EngineSensors/EngineSensors.h"
#include "../../Exchange/Protocols/VoltageRegulators/VoltageRegulators.h"

class DisplayingSensors : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayingSensors(QWidget *parent = nullptr);

    void setEngineSensorsData(std::string_view data);
    void setVoltageRegulatorsSensorsData(std::string_view data);
    void setSensorsDataLimits(const std::shared_ptr<HashLimits> &newSensorsDataLimits);
    void addNewDataLabels(std::vector<SensorName> &list);

public slots:
    void addWidgets(std::string_view);
    void checkRangeValues(QLabel *, int val, SensorLimits lim);

private:    
    QVBoxLayout *mainLayout;
    EngineSensors::EngineSensors *engineSensors;
    VoltageRegulators::VoltageRegulators *voltageRegulatorsSensors;
    VibrationDirection *vibrationDirection;
    QMap<QString, QLabel *> sensorsDataLabels;

    std::shared_ptr<HashLimits> sensorsDataLimits;
};

#endif // DISPLAYINGSENSORS_H
