#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
    sensorsTableWdg(new SensorsTableWidget(this))
{
    sensorsTableWdg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setCentralWidget(sensorsTableWdg); // Устанавливаем центральный виджет
}
