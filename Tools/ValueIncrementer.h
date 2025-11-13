/**
 * \file ValueIncrementer.h
 * \brief Таймер‑инкрементатор значения для тестов/демо.
 * \details Плавно увеличивает значение от min до max за заданное время в секундах, генерируя сигнал при изменении.
 */

#ifndef VALUEINCREMENTER_H
#define VALUEINCREMENTER_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QObject>
#include <QTimer>
#include <QDebug>
#endif

/**\class ValueIncrementer
 * \brief Плавно увеличивает значение от \c m_min до \c m_max за заданное время.
 * \details Используется для тестирования/демо UI. Опирается на QTimer с шагом 1 сек.
 */

class ValueIncrementer : public QObject
{
    Q_OBJECT

public:
    ValueIncrementer(uint16_t min, uint16_t max, uint16_t timeSeconds, QObject* parent = nullptr);

    void start();

    double value() const;
    void stopThis();
signals:
    void valueChanged(double newVal);
    void finished();

private slots:
    void updateValue();

private:
    double m_min;
    double m_max;
    int m_time;       // время в секундах
    double m_val;
    double m_step;
    QTimer* m_timer;

    bool stop = false;
};


#endif // VALUEINCREMENTER_H
