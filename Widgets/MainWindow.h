#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>

#include "Exchange/Protocols/SensorsFrames.h"
#include "SensorsTable/SensorsTableWidget.h"
#include "SensorsTable/ListOfLimitsWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void close();
    void openListOfLimits();
    void openListOfLimitsWdgt();

private:
    std::shared_ptr<SensorsFrames> sensorsManager;
    SensorsTableWidget  *sensorsTableWdgt;
    ListOfLimitsWidget  *listOfLimitsWdgt;

};

#endif // MAINWINDOW_H
