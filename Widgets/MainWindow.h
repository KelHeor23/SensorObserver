#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>

#include "SensorsTable/SensorsTableWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void close();
    void openListOfLimits();

private:
    SensorsTableWidget *sensorsTableWdg;
};

#endif // MAINWINDOW_H
