/**
 * \file VibrationDirection.h
 * \brief Виджет индикации направления вибраций.
 * \details Отображает оценённое направление/амплитуду вибраций на основе входных значений сенсоров. Предназначен для быстрой диагностики перекосов/разбаланса.
 */

#ifndef VIBRATIONDIRECTION_H
#define VIBRATIONDIRECTION_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#endif
/**\class VibrationDirection
 * \brief Визуализирует направление/амплитуду вибраций.
 * \details Использует входные значения сенсоров для расчёта вектора и окраски зон.
 */

class VibrationDirection : public QGraphicsView {
public:
    VibrationDirection(QWidget *parent = nullptr);

    void update(int len, int degree);

private:
    QGraphicsScene *scene;
    QGraphicsEllipseItem *circle = nullptr;
};

#endif // VIBRATIONDIRECTION_H
