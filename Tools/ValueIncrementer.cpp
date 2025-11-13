/**
 * \file ValueIncrementer.cpp
 * \brief Реализация ValueIncrementer: настройка QTimer, вычисление шага, инкремент.
 * \details Запускает периодическое обновление раз в секунду, корректно обрабатывает крайние случаи (max==min, time=0).
 */

#include "ValueIncrementer.h"
/** \brief Инициализация таймера и расчёт шага на секунду. */

ValueIncrementer::ValueIncrementer(uint16_t min, uint16_t max, uint16_t timeSeconds, QObject *parent)
    : QObject(parent), m_min(min), m_max(max), m_time(timeSeconds), m_val(min)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000); // 1 секунда

    // Вычисляем шаг увеличения за 1 секунду
    if (timeSeconds > 0)
        m_step = (max - min) / timeSeconds;
    else
        m_step = 0;

    connect(m_timer, &QTimer::timeout, this, &ValueIncrementer::updateValue);
}

void ValueIncrementer::start()
{
    m_val = m_min;
    qDebug() << "Start value:" << m_val;
    m_timer->start();
}

double ValueIncrementer::value() const { return m_val; }

void ValueIncrementer::stopThis()
{
    stop = true;
}

void ValueIncrementer::updateValue()
{
    if (!stop){
        if (m_val < m_max) {
            m_val += m_step;
            if (m_val > m_max)
                m_val = m_max;

            qDebug() << "Updated value:" << m_val;
            emit valueChanged(m_val);
        } else {
            stop = false;
            m_timer->stop();
            emit finished();
            qDebug() << "Finished at value:" << m_val;
        }
    } else {
        stop = false;
        m_timer->stop();
        emit finished();
        qDebug() << "Finished at value:" << m_val;
    }
}
