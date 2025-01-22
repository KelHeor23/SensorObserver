#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>

#include "SensorsTable/ListOfLimits.h"
#include "../Exchange/Client.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

private:
    QHBoxLayout *hBoxLayout;
    ListOfLimits *listOfLimits;
    Client *client;
};

#endif // MAINWINDOW_H
