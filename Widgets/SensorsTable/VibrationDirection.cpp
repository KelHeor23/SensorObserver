/**
 * \file VibrationDirection.cpp
 * \brief Реализация виджета направления вибраций.
 * \details Рисует стрелку/маркер направления и масштабирует длину по амплитуде; обновляет подписи и цвета зон.
 */

#include "VibrationDirection.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <cmath>
#endif
/** \brief Инициализирует виджет и связывает сигналы обновления данных. */

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
    int x = len * std::cos(angleRadians) - 5;
    int y = len * std::sin(angleRadians) - 5;

    circle = new QGraphicsEllipseItem(x, y, 10, 10);

    scene->addItem(circle);
}
