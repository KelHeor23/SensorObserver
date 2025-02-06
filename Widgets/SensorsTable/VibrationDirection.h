#ifndef VIBRATIONDIRECTION_H
#define VIBRATIONDIRECTION_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

class VibrationDirection : public QGraphicsView {
public:
    VibrationDirection(QWidget *parent = nullptr);

    void update(int len, int degree);

private:
    QGraphicsScene *scene;
    QGraphicsEllipseItem *circle = nullptr;
};

#endif // VIBRATIONDIRECTION_H
