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

public slots:
    void addWidgets();

private:    
    QVBoxLayout *mainLayout;
    EngineSensors::EngineSensors *sensors;
    VibrationDirection *vibrationDirection;    
};

#endif // DISPLAYINGSENSORS_H
