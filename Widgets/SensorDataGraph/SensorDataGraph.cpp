#include "SensorDataGraph.h"

SensorDataGraph::SensorDataGraph(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent)
    : QWidget{parent}
    , mainLt(new QVBoxLayout)
    , m_plot(new QCustomPlot(this))
    , sensorsListTreeWdgt(new QTreeWidget)
    , sensorsManager(sensorsManager_t)
{
    setWindowTitle("График данных");

    setLayout(mainLt);

    QHBoxLayout *hboxLt = new QHBoxLayout;
    hboxLt->addWidget(m_plot);
    hboxLt->addWidget(sensorsListTreeWdgt);
    mainLt->addLayout(hboxLt);

    fillSensorsList();
    setDarkstyle();

    m_plot->addGraph();
    m_plot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    m_plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    m_plot->addGraph();
    m_plot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
        x[i] = i;
        y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
        y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_plot->xAxis2->setVisible(true);
    m_plot->xAxis2->setTickLabels(false);
    m_plot->yAxis2->setVisible(true);
    m_plot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(m_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    m_plot->graph(0)->setData(x, y0);
    m_plot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    m_plot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    m_plot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called m_plot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    m_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void SensorDataGraph::setDarkstyle()
{
    m_plot->setMinimumSize(QSize(1000, 1000));
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

void SensorDataGraph::fillSensorsList()
{
    sensorsListTreeWdgt->setHeaderHidden(true); // Скрываем заголовок
    sensorsListTreeWdgt->setMinimumWidth(200);
    sensorsListTreeWdgt->setMaximumWidth(300);

    // Пример данных: группы и элементы
    QList<QPair<QString, QStringList>> groups = {
        {"Fruits", {"Apple", "Banana", "Orange"}},
        {"Vegetables", {"Carrot", "Broccoli", "Spinach"}},
        {"Colors", {"Red", "Green", "Blue"}}
    };

    // Заполняем дерево
    for (const auto &group : groups) {
        // Создаем группу (родительский элемент)
        QTreeWidgetItem *groupItem = new QTreeWidgetItem(sensorsListTreeWdgt);
        groupItem->setText(0, group.first);
        groupItem->setFlags(Qt::ItemIsEnabled); // Группа без чекбокса

        // Добавляем элементы в группу
        for (const QString &item : group.second) {
            QTreeWidgetItem *childItem = new QTreeWidgetItem(groupItem);
            childItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            childItem->setCheckState(0, Qt::Unchecked);
            childItem->setText(0, item);
        }
        // Разворачиваем группу по умолчанию
        groupItem->setExpanded(true);
    }

    // Обработка изменений состояния чекбоксов
    QObject::connect(sensorsListTreeWdgt, &QTreeWidget::itemChanged, [](QTreeWidgetItem *item, int column) {
        if (column != 0) return;
        qDebug() << "Item changed:" << item->text(0) << "State:" << item->checkState(0);
    });
}
