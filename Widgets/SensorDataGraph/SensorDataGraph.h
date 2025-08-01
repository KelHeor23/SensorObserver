#ifndef SENSORDATAGRAPH_H
#define SENSORDATAGRAPH_H

#include <QtWidgets/QWidget>
#include <QTreeWidget>
#include <QTimer>

#include "Exchange/Protocols/SensorsFrames.h"
#include "qcustomplot.h"

class SensorDataGraph : public QWidget
{
    Q_OBJECT
public:
    explicit SensorDataGraph(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent = nullptr);

private:
    void settingPlot();
    void setDarkstyle();
    void fillSensorsList();
    QColor getColor();

private slots:
    void onItemChanged(QTreeWidgetItem *item, int column);
    void addNewData();
    void updateGraph();

signals:

private:
    QVBoxLayout *mainLt;
    QCustomPlot *m_plot;
    QTreeWidget *sensorsListTreeWdgt;
    QTimer      *m_timer;

    std::shared_ptr<SensorsFrames> sensorsManager;
    QMap<QString, QCPGraph*> graphMap;
};

#endif // SENSORDATAGRAPH_H
