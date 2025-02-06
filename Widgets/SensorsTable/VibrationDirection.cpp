#include "VibrationDirection.h"
#include <cmath>

VibrationDirection::VibrationDirection(QWidget *parent)
    : QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    // Создаем сцену
    scene = new QGraphicsScene(this);
    setScene(scene);

    // Устанавливаем область сцены
    scene->setSceneRect(-100, -100, 200, 200); // Устанавливаем размеры сцены

    // Добавляем оси
    scene->addLine(QLineF(-200, 0, 200, 0), QPen(Qt::black)); // Ось X
    scene->addLine(QLineF(0, -200, 0, 200), QPen(Qt::black)); // Ось Y

    // Устанавливаем фон
    setBackgroundBrush(Qt::white);
}

void VibrationDirection::update(int len, int degree)
{
    if (circle) {
        scene->removeItem(circle);
        delete circle;
        circle = nullptr;
    }

    // Преобразование угла из градусов в радианы
    double angleRadians = degree * M_PI / 180.0;

    // Расчет координат
    int x = len * std::cos(angleRadians);
    int y = len * std::sin(angleRadians);

    circle = new QGraphicsEllipseItem(x, y, 10, 10);

    scene->addItem(circle);
}

