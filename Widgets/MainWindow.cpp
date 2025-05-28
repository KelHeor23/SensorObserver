#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    ,sensorsManager(std::make_shared<SensorsFrames>())
    ,sensorsTableWdgt(new SensorsTableWidget(this))
    ,listOfLimitsWdgt(new ListOfLimitsWidget())
{
    QMenu *fileMenu = this->menuBar()->addMenu(tr("Файл"));
    QAction *closeAction = new QAction(tr("Закрыть"), this);
    fileMenu->addAction(closeAction);
    connect(closeAction, &QAction::triggered, this, &MainWindow::close);

    QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
    QAction *openListOfLimitsAction = new QAction(tr("Открыть список переделов"), this);
    viewMenu->addAction(openListOfLimitsAction);
    connect(openListOfLimitsAction, &QAction::triggered, this, &MainWindow::openListOfLimits);

    QMenu *settingsMenu = menuBar()->addMenu(tr("Настройки"));
    QAction *openLOLAction = new QAction(tr("Список сенсоров"), this);
    settingsMenu->addAction(openLOLAction);
    connect(openLOLAction, &QAction::triggered, this, &MainWindow::openListOfLimitsWdgt);

    sensorsTableWdgt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setCentralWidget(sensorsTableWdgt); // Устанавливаем центральный виджет

    listOfLimitsWdgt->addNewFrame(sensorsManager->getEngineSensors());
}

void MainWindow::close()
{
    this->close();
}

void MainWindow::openListOfLimits()
{
    sensorsTableWdgt->toggleLimitsVisibility();
}

void MainWindow::openListOfLimitsWdgt()
{
    listOfLimitsWdgt->show();
}
