#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , sensorsManager(std::make_shared<SensorsFrames>())
    , sensorsTableWdgt(new SensorsTableWidget(sensorsManager, this))
    , listOfLimitsWdgt(new ListOfLimitsWidget())
    , connSettingsWdgt(new ConnSettings())
    , ipConnectionLbl(new QLabel("IP адрес бортового компьютера: ", this))
{
    QMenu *fileMenu = this->menuBar()->addMenu(tr("Файл"));
    QAction *closeAction = new QAction(tr("Закрыть"), this);
    fileMenu->addAction(closeAction);
    connect(closeAction, &QAction::triggered, this, &MainWindow::close);

    QMenu *settingsMenu = menuBar()->addMenu(tr("Настройки"));
    QAction *openLOLAction = new QAction(tr("Список сенсоров"), this);
    settingsMenu->addAction(openLOLAction);
    connect(openLOLAction, &QAction::triggered, this, &MainWindow::openListOfLimitsWdgt);

    QAction *openConnAction = new QAction(tr("Настрока подключения"), this);
    settingsMenu->addAction(openConnAction);
    connect(openConnAction, &QAction::triggered, this, &MainWindow::openСonnSettingsWdgt);

    sensorsTableWdgt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setCentralWidget(sensorsTableWdgt); // Устанавливаем центральный виджет

    for (auto it : sensorsManager->getFrames()){
        listOfLimitsWdgt->addNewFrame(it.second);
    }

    statusBar()->addPermanentWidget(ipConnectionLbl); // добавляет справа, не убирается при showMessage
}

void MainWindow::close()
{
    this->close();
}

void MainWindow::openListOfLimitsWdgt()
{
    listOfLimitsWdgt->show();
}

void MainWindow::openСonnSettingsWdgt()
{
    connSettingsWdgt->show();
}
