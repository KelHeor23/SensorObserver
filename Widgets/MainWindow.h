#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>

#include "Exchange/Protocols/SensorsFrames.h"
#include "SensorsTable/SensorsTableWidget.h"
#include "SensorsTable/ListOfLimitsWidget.h"
#include "Common/ConnSettings.h"
#include "Other/MotorControl.h"
#include "Other/SmoothMotorControl.h"
#include "Widgets/SensorDataGraph/SensorDataGraph.h"

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
    ListOfLimitsWidget  *listOfLimitsWdgt;
    SensorDataGraph     *sensorDataGraphWdgt;
    QLabel              *ipConnectionLbl;    
};

#endif // MAINWINDOW_H
