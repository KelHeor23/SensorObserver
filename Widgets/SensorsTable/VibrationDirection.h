#ifndef VIBRATIONDIRECTION_H
#define VIBRATIONDIRECTION_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

#include "../../Exchange/Protocols/EngineSensors/EngineSensors.h"

class VibrationDirection : public QGraphicsView {
public:
    VibrationDirection(EngineSensors::EngineSensors &sensors, QWidget *parent = nullptr);
};

#endif // VIBRATIONDIRECTION_H
