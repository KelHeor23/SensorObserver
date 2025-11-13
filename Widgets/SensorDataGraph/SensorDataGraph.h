/**
 * \file SensorDataGraph.h
 * \brief Виджет отображения временных рядов сенсоров на QCustomPlot.
 * \details Список доступных сенсоров и графиков, таймер обновления, структуры ключей выбранных данных.
 */

#ifndef SENSORDATAGRAPH_H
#define SENSORDATAGRAPH_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QtWidgets/QWidget>
#include <QTreeWidget>
#include <QTimer>
#endif

#include "Data/Frames/Containers/SensorsFrames.h"
#include "qcustomplot.h"
/**
 * \struct DataFullName
 * \brief Полный ключ временного ряда: двигатель, фрейм, сенсор.
 * \details Используется для адресации данных при построении графиков.
 */

struct DataFullName {
    size_t  engineNum;
    QString frameName;
    QString sensorName;

    bool operator==(const DataFullName& other) const {
        return engineNum == other.engineNum &&
               frameName == other.frameName &&
               sensorName == other.sensorName;
    }
};

namespace std {
template<>
struct hash<DataFullName> {
    size_t operator()(const DataFullName& key) const {
        size_t h1 = qHash(key.frameName);
        size_t h2 = qHash(key.sensorName);
        size_t h3 = hash<size_t>()(key.engineNum);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};
}
/**\class SensorDataGraph
 * \brief Виджет построения графиков значений сенсоров.
 * \details Отображает дерево доступных сенсоров и график.
 * Обновляет окно по таймеру и ограничивает количество точек.
 */

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

    std::unordered_map<DataFullName, size_t> dataSize;
};

#endif // SENSORDATAGRAPH_H
