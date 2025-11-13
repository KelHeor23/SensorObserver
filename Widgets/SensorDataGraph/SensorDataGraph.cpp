/**
 * \file SensorDataGraph.cpp
 * \brief Реализация SensorDataGraph: построение и обновление графиков.
 * \details Обновляет видимую область по времени окна, ограничивает количество точек, масштабирует ось Y.
 */

#include "SensorDataGraph.h"
#include "Data/DataStructure.h"

/** \brief Инициализирует график, дерево сенсоров и таймер обновления. */

SensorDataGraph::SensorDataGraph(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent)
    : QWidget{parent}
    , mainLt(new QVBoxLayout)
    , m_plot(new QCustomPlot(this))
    , sensorsListTreeWdgt(new QTreeWidget)
    , sensorsManager(sensorsManager_t)
    , m_timer(new QTimer(this))
{
    setWindowTitle("График данных");

    setLayout(mainLt);

    QHBoxLayout *hboxLt = new QHBoxLayout;
    hboxLt->addWidget(m_plot);
    hboxLt->addWidget(sensorsListTreeWdgt);
    mainLt->addLayout(hboxLt);

    fillSensorsList();
    settingPlot();

    connect(m_timer, &QTimer::timeout, this, &SensorDataGraph::addNewData);
    m_timer->start(100);  // мс интервал

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SensorDataGraph::updateGraph); // updateGraph — ваш слот для обновления данных и графика
    timer->start(100); // интервалы 200 мс
}

void SensorDataGraph::settingPlot()
{
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss.zzz");

    m_plot->xAxis->setTicker(dateTicker);
    m_plot->setNotAntialiasedElements(QCP::aeAll);
    m_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    m_plot->setNoAntialiasingOnDrag(true);
    m_plot->setPlottingHints(QCP::phFastPolylines);
    m_plot->setBufferDevicePixelRatio(1); // Отключаем сглаживание для HiDPI
    m_plot->legend->setVisible(true);
    m_plot->legend->setFont(QFont("Helvetica", 9));
    setDarkstyle();
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
    QList<QPair<QString, QStringList>> groups;

    for (auto &it : sensorsManager->getFrames()) {
        QPair<QString, QStringList> temp;
        temp.first = QString::fromStdString(it.second->getNameFrame());
        for (auto &field : it.second->getFields())
            temp.second.push_back(QString::fromStdString(field.first));
        groups.push_back(temp);
    }

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
        groupItem->setExpanded(false);
    }

    // Обработка изменений состояния чекбоксов
    QObject::connect(sensorsListTreeWdgt, &QTreeWidget::itemChanged, this, &SensorDataGraph::onItemChanged);
}

QColor SensorDataGraph::getColor()
{
    static int i = 0;
    QColor color = QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80);
    i++;
    return color;
}

void SensorDataGraph::onItemChanged(QTreeWidgetItem *item, int column)
{
    if (column != 0) return;

    QString sensorName = item->text(0);
    QString groupName = item->parent()->text(0);

    DataFullName frame;
    frame.engineNum = 0;
    frame.frameName = groupName;
    frame.sensorName = sensorName;

    bool isChecked = (item->checkState(0) == Qt::Checked);

    if (isChecked) {
        QCPGraph *graph = m_plot->addGraph();
        graph->setLineStyle(QCPGraph::lsLine);
        graph->setAdaptiveSampling(true); // Включите адаптивную выборку
        graph->setName(sensorName);

        QString parentText = item->parent()->text(0);
        graphMap[sensorName] = graph;

        // Настраиваем внешний вид
        QColor color(getColor());
        graph->setPen(QPen(color, 2));
        graph->setName(sensorName);

        auto &time = DataStructure::Instance().engines[0][groupName.toStdString()]["Time"];
        auto &data = DataStructure::Instance().engines[0][groupName.toStdString()][sensorName.toStdString()];

        graph->setData(QVector<double>(time.begin(), time.end()), QVector<double>(data.begin(), data.end()));

        dataSize[frame] = DataStructure::Instance().engines[0][groupName.toStdString()]["Time"].size();
    } else {
        if (graphMap.contains(sensorName)) {
            dataSize.erase(frame);
            m_plot->removeGraph(graphMap[sensorName]);
            graphMap.remove(sensorName);
        }
    }
}

void SensorDataGraph::addNewData()
{
    for (auto &it : dataSize) {
        auto &data = DataStructure::Instance().engines[it.first.engineNum][it.first.frameName.toStdString()][it.first.sensorName.toStdString()];
        if (data.size() > it.second) {
            auto &graph = graphMap[it.first.sensorName];
            for (int i = it.second; i < data.size(); i++){
                auto &time = DataStructure::Instance().engines[0][it.first.frameName.toStdString()]["Time"];
                auto &data = DataStructure::Instance().engines[0][it.first.frameName.toStdString()][it.first.sensorName.toStdString()];

                graph->setData(QVector<double>(time.begin(), time.end()), QVector<double>(data.begin(), data.end()));
            }
            it.second = data.size();
        }
    }
}
/**
 * \brief Обновляет видимую область и добавляет новые точки для выбранных сенсоров.
 * \details Двигает окно по времени, удаляет старые точки (например, хранит ~N последних секунд),
 * масштабирует ось Y по текущим данным и инициирует перерисовку.
 */


void SensorDataGraph::updateGraph()
{
    int time = 20;
    double now = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.;
    m_plot->xAxis->setRange(now - time, now);

    // Ограничиваем количество точек для каждого графика
    for (auto it = graphMap.begin(); it != graphMap.end(); ++it) {
        QCPGraph* graph = it.value();
        if (graph->data()->size() > 5000) { // Максимум 5000 точек на график
            graph->data()->removeBefore(now - time); // Удаляем старые данные
        }
    }
    // Масштабируем только ось Y по данным
    m_plot->yAxis->rescale();
    m_plot->replot(QCustomPlot::rpQueuedReplot);
}

