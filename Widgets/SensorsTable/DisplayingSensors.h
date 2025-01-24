#ifndef DISPLAYINGSENSORS_H
#define DISPLAYINGSENSORS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "VibrationDirection.h"

class DisplayingSensors : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayingSensors(QWidget *parent = nullptr);

public slots:
    void addWidgets();

private:
    QVBoxLayout *mainLayout;
    VibrationDirection *vibrationDirection;
};

#endif // DISPLAYINGSENSORS_H
