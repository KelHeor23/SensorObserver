/**
 * \file MainWindow.h
 * \brief Главное окно приложения телеметрии.
 * \details Создаёт/связывает менеджер фреймов, таблицу сенсоров, графики, виджеты управления и подключение к дрону.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#endif

#include "Data/Frames/Containers/SensorsFrames.h"
#include "Exchange/DataReader.h"
#include "SensorsTable/SensorsTableWidget.h"
#include "SensorsTable/ListOfLimitsWidget.h"
#include "Common/ConnSettings.h"
#include "Other/MotorControl.h"
#include "Other/SmoothMotorControl.h"
#include "Widgets/SensorDataGraph/SensorDataGraph.h"

/**\class MainWindow
 * \brief Главное окно интерфейса оператора.
 * \details Создаёт подключение, таблицы сенсоров, графики и панели управления двигателями.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void close();
    void openListOfLimitsWdgt();
    void openСonnSettingsWdgt();
    void openMotorControlWdgt();
    void openSmoothMotorControlWdgt();
    void openDataGraphWdgt();
    void reconnect();

private:
    std::shared_ptr<SensorsFrames> sensorsManager;
    ConnSettings        *connSettingsWdgt;
    MotorControl        *motorControlWdgt;
    SmoothMotorControl  *smoothMotorControlWdgt;
    Client              *client;
    SensorsTableWidget  *sensorsTableWdgt;
    DataReader          *dataReader;
    ListOfLimitsWidget  *listOfLimitsWdgt;
    SensorDataGraph     *sensorDataGraphWdgt;
    QLabel              *ipConnectionLbl;
};

#endif // MAINWINDOW_H
