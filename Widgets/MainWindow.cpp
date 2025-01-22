#include "MainWindow.h"

#include "../Exchange/Client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    Client client;
}
