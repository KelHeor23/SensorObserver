#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>

#include "Exchange/Protocols/SensorsFrames.h"
#include "SensorsTable/SensorsTableWidget.h"
#include "SensorsTable/ListOfLimitsWidget.h"
#include "Common/ConnSettings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void close();
    void openListOfLimitsWdgt();
    void openСonnSettingsWdgt();

private:
    std::shared_ptr<SensorsFrames> sensorsManager;
    SensorsTableWidget  *sensorsTableWdgt;
    ListOfLimitsWidget  *listOfLimitsWdgt;
    ConnSettings        *connSettingsWdgt;
    QLabel              *ipConnectionLbl;

};

#endif // MAINWINDOW_H
