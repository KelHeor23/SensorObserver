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

    setDarkstyle();
}

void SensorDataGraph::setDarkstyle()
{
    m_plot->xAxis->setBasePen(QPen(Qt::white, 1));
    m_plot->yAxis->setBasePen(QPen(Qt::white, 1));
    m_plot->xAxis->setTickPen(QPen(Qt::white, 1));
    m_plot->yAxis->setTickPen(QPen(Qt::white, 1));
    m_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    m_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    m_plot->xAxis->setTickLabelColor(Qt::white);
    m_plot->yAxis->setTickLabelColor(Qt::white);
    m_plot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_plot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    m_plot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_plot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    m_plot->xAxis->grid()->setSubGridVisible(true);
    m_plot->yAxis->grid()->setSubGridVisible(true);
    m_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    m_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    m_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    m_plot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    m_plot->axisRect()->setBackground(axisRectGradient);
}
