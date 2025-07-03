#include "Client.h"

#include <QHostAddress>

Client::Client(QObject *parent)
    : QObject(parent)
    , conSettings(new QSettings("settings", "conSettings", this))
{
    socket = new QTcpSocket(this);
    reconnectTimer = new QTimer(this);
    reconnectTimer->setInterval(3000); // 30 секунд

    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readData);
    connect(reconnectTimer, &QTimer::timeout, this, &Client::connectToServer);

    loadSettings();
    connectToServer(); // Первая попытка подключения
}

Client::~Client()
{
    socket->close();
    delete socket;
    delete reconnectTimer;
}

void Client::connectToServer()
{
    static int i = 0;
    if (reconnectTimer->isActive()) {
        reconnectTimer->stop(); // Остановить таймер перед новой попыткой
    }

    socket->connectToHost(QHostAddress(droneIP), dronePort); // Замените на адрес и порт вашего сервера
    if (socket->waitForConnected(1000)) {
        qDebug() << "Connected to server";        
        reconnectTimer->stop(); // Остановить таймер, если подключение успешно
    } else {
        qDebug() << "Connection failed. Trying again..." << i++;
        reconnectTimer->start(); // Запустить таймер для повторных попыток
    }
}

void Client::connected()
{
    emit connEnable();
    reconnectTimer->stop(); // Остановить таймер при успешном подключении
    qDebug() << "Connected to server";    
}

void Client::disconnected()
{
    qDebug() << "Disconnected. Trying to reconnect...";
    reconnectTimer->start(); // Запустить таймер для повторных попыток
    emit connDisable();
}

void Client::readData()
{
    QByteArray data = socket->readAll();
    buffer.append(data); // Записать данные в буфер    

    emit engineSensorsDataSent(data);
    emit connEnable();
}

void Client::setDronePort(quint16 newDronePort)
{
    dronePort = newDronePort;
}

void Client::sendMsg(const QByteArray &data)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data); // Отправляем данные через сокет
        socket->flush();     // Немедленная отправка без ожидания
    }
}

void Client::loadSettings()
{
    droneIP    = conSettings->value("droneIP", "localhost").toString();
    dronePort  = conSettings->value("dronePort", 8002).toInt();
}

void Client::setDroneIP(const QString &newDroneIP)
{
    droneIP = newDroneIP;
}
