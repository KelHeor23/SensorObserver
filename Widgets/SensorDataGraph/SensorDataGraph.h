#ifndef SENSORDATAGRAPH_H
#define SENSORDATAGRAPH_H

#include <QtWidgets/QWidget>

#include "qcustomplot.h"

class SensorDataGraph : public QWidget
{
    Q_OBJECT
public:
    explicit SensorDataGraph(QWidget *parent = nullptr);

private:
    void setDarkstyle();

signals:

private:
    QVBoxLayout *mainLt;
    QCustomPlot *m_plot;
};

#endif // SENSORDATAGRAPH_H
