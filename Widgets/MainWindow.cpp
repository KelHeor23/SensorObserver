#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
    sensorsTableWdg(new SensorsTableWidget(this))
{
    QMenu *fileMenu = this->menuBar()->addMenu(tr("Файл"));
    QAction *closeAction = new QAction(tr("Закрыть"), this);
    fileMenu->addAction(closeAction);
    connect(closeAction, &QAction::triggered, this, &MainWindow::close);

    QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
    QAction *openListOfLimitsAction = new QAction(tr("Открыть список переделов"), this);
    viewMenu->addAction(openListOfLimitsAction);
    connect(openListOfLimitsAction, &QAction::triggered, this, &MainWindow::openListOfLimits);

    sensorsTableWdg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setCentralWidget(sensorsTableWdg); // Устанавливаем центральный виджет
}

void MainWindow::close()
{
    this->close();
}

void MainWindow::openListOfLimits()
{
    sensorsTableWdg->toggleLimitsVisibility();
}
