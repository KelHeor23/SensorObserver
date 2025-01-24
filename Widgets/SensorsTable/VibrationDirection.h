#ifndef VIBRATIONDIRECTION_H
#define VIBRATIONDIRECTION_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

class VibrationDirection : public QGraphicsView {
public:
    VibrationDirection(QWidget *parent = nullptr);
};

#endif // VIBRATIONDIRECTION_H
