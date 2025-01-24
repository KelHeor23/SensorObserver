#include "VibrationDirection.h"


VibrationDirection::VibrationDirection(QWidget *parent)
    : QGraphicsView(parent)
{
    // Создаем сцену
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    // Устанавливаем область сцены
    scene->setSceneRect(-100, -100, 200, 200); // Устанавливаем размеры сцены

    // Добавляем оси
    scene->addLine(QLineF(-200, 0, 200, 0), QPen(Qt::black)); // Ось X
    scene->addLine(QLineF(0, -200, 0, 200), QPen(Qt::black)); // Ось Y

    // Устанавливаем фон
    setBackgroundBrush(Qt::white);
}
