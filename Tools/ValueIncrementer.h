#ifndef VALUEINCREMENTER_H
#define VALUEINCREMENTER_H

#include <QtCore/QObject>

#include <QObject>
#include <QTimer>
#include <QDebug>

class ValueIncrementer : public QObject
{
    Q_OBJECT

public:
    ValueIncrementer(double min, double max, int timeSeconds, QObject* parent = nullptr);

    void start();

    double value() const;

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
};


#endif // VALUEINCREMENTER_H
