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

    QMenu *dataMenu = menuBar()->addMenu(tr("Данные"));
    QAction *openSensorGraphAction = new QAction(tr("Открыть в виде графика"), this);
    dataMenu->addAction(openSensorGraphAction);
    connect(openSensorGraphAction, &QAction::triggered, this, &MainWindow::openDataGraphWdgt);

    QMenu *settingsMenu = menuBar()->addMenu(tr("Настройки"));
    QAction *openLOLAction = new QAction(tr("Список сенсоров"), this);
    settingsMenu->addAction(openLOLAction);
    connect(openLOLAction, &QAction::triggered, this, &MainWindow::openListOfLimitsWdgt);

    QAction *openConnAction = new QAction(tr("Настрока подключения"), this);
    settingsMenu->addAction(openConnAction);
    connect(openConnAction, &QAction::triggered, this, &MainWindow::openСonnSettingsWdgt);

    QMenu *otherMenu = menuBar()->addMenu(tr("Другое"));
    QAction *motorAction = new QAction(tr("Управление двигателями"), this);
    otherMenu->addAction(motorAction);
    connect(motorAction, &QAction::triggered, this, &MainWindow::openMotorControlWdgt);

    QAction *smoothMotorAction = new QAction(tr("Плавное управление двигателями"), this);
    otherMenu->addAction(smoothMotorAction);
    connect(smoothMotorAction, &QAction::triggered, this, &MainWindow::openSmoothMotorControlWdgt);

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

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapInterval(0); // Отключаем VSync для максимальной производительности
    QSurfaceFormat::setDefaultFormat(format);
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

void MainWindow::openMotorControlWdgt()
{
    motorControlWdgt = new MotorControl(client);
    motorControlWdgt->setAttribute(Qt::WA_DeleteOnClose);
    motorControlWdgt->show();
}

void MainWindow::openSmoothMotorControlWdgt()
{
    smoothMotorControlWdgt = new SmoothMotorControl(client);
    smoothMotorControlWdgt->setAttribute(Qt::WA_DeleteOnClose);
    smoothMotorControlWdgt->show();
}

void MainWindow::openDataGraphWdgt()
{
    sensorDataGraphWdgt = new SensorDataGraph(sensorsManager);
    sensorDataGraphWdgt->setAttribute(Qt::WA_DeleteOnClose);
    sensorDataGraphWdgt->show();
}

void MainWindow::reconnect()
{
    client->setDroneIP(connSettingsWdgt->getDroneIP());
    client->setDronePort(connSettingsWdgt->getDronePort());
    ipConnectionLbl->setText("Drone IP:" + connSettingsWdgt->getDroneIP() + ":" + QString::number(connSettingsWdgt->getDronePort()));
}
