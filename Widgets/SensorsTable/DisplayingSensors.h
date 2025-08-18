#ifndef DISPLAYINGSENSORS_H
#define DISPLAYINGSENSORS_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "Data/Frames/Containers/SensorsFrames.h"
#include "Tools/ColorProgressBar.h"

class DisplayingSensors : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayingSensors(std::shared_ptr<SensorsFrames> sensorManager_t, QWidget *parent = nullptr);

    void setSensorsData(FrameTypes type, std::string_view data, int16_t node_id);
    void addNewDataLabels(std::vector<SensorName> &list);

    void linkLimitsSensorsFrames(std::shared_ptr<SensorsFrames>);
    void linkFrame(FrameTypes type, std::shared_ptr<SensorsFrames> target);

    std::shared_ptr<SensorsFrames> getSensorManager() const;

public slots:
    void addWidgets(std::string_view);
    //void checkRangeValues(QLabel *, std::shared_ptr<SensorData> field);
    void checkRangeValues(ColorProgressBar *, std::shared_ptr<SensorData> field);

private:    
    QGridLayout *mainLayout;
    std::shared_ptr<SensorsFrames> sensorManager;
    std::unordered_map<QString, QLabel *> sensorsDataLabels;
    std::unordered_map<QString, ColorProgressBar *> sensorsColorProgressBarDataLabels;
};

#endif // DISPLAYINGSENSORS_H
