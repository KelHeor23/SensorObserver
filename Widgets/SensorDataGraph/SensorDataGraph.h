#ifndef SENSORDATAGRAPH_H
#define SENSORDATAGRAPH_H

#include <QtWidgets/QWidget>
#include <QTreeWidget>

#include "Exchange/Protocols/SensorsFrames.h"
#include "qcustomplot.h"

class SensorDataGraph : public QWidget
{
    Q_OBJECT
public:
    explicit SensorDataGraph(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent = nullptr);

private:
    void setDarkstyle();
    void fillSensorsList();

signals:

private:
    QVBoxLayout *mainLt;
    QCustomPlot *m_plot;
    QTreeWidget *sensorsListTreeWdgt;

    std::shared_ptr<SensorsFrames> sensorsManager;
};

#endif // SENSORDATAGRAPH_H
