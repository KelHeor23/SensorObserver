#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>

#include "SensorsTable/ListOfLimits.h"
#include "SensorsTable/DisplayingSensors.h"
#include "../Exchange/Client.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void fillSensorsEngines();
signals:

private:
    EngineSensors::Limits *engineSensorsLimits;

    QHBoxLayout *hBoxLayout;
    ListOfLimits *listOfLimits;
    DisplayingSensors *sensorsEngine_1;
    DisplayingSensors *sensorsEngine_2;
    DisplayingSensors *sensorsEngine_3;
    DisplayingSensors *sensorsEngine_4;
    Client *client;    
};

#endif // MAINWINDOW_H
