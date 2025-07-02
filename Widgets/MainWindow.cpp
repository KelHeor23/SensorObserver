#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , sensorsManager(std::make_shared<SensorsFrames>())
    , connSettingsWdgt(new ConnSettings())
    , client(new Client(this))
    , sensorsTableWdgt(new SensorsTableWidget(sensorsManager, client, this))
    , listOfLimitsWdgt(new ListOfLimitsWidget())    
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

    ipConnectionLbl->setStyleSheet("color: orange;");
    statusBar()->addPermanentWidget(ipConnectionLbl); // добавляет справа, не убирается при showMessage
    reconnect();
    connect(connSettingsWdgt, &ConnSettings::newConnSettings, this, &MainWindow::reconnect);
    connect(client, &Client::connEnable, [this](){ipConnectionLbl->setStyleSheet("color: green;");});
    connect(client, &Client::connDisable, [this](){ipConnectionLbl->setStyleSheet("color: red;");});
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

void MainWindow::reconnect()
{
    client->setDroneIP(connSettingsWdgt->getDroneIP());
    client->setDronePort(connSettingsWdgt->getDronePort());
    ipConnectionLbl->setText("Drone IP:" + connSettingsWdgt->getDroneIP() + ":" + QString::number(connSettingsWdgt->getDronePort()));
}
