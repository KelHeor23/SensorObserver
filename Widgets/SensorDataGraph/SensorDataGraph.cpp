#include "SensorDataGraph.h"

SensorDataGraph::SensorDataGraph(QWidget *parent)
    : QWidget{parent}
    , mainLt(new QVBoxLayout)
    , m_plot(new QCustomPlot(this))
{
    setWindowTitle("График данных");
    mainLt->addWidget(m_plot);
    setLayout(mainLt);
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    m_plot->addGraph();
    m_plot->graph(0)->setData(x, y);
    // give the axes some labels:
    m_plot->xAxis->setLabel("x");
    m_plot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    m_plot->xAxis->setRange(-1, 1);
    m_plot->yAxis->setRange(0, 1);
    m_plot->replot();
}
