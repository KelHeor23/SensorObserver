#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QSettings>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void setDroneIP(const QString &newDroneIP);

    void setDronePort(quint16 newDronePort);

private:
    void loadSettings();

public slots:
    void connectToServer();
    void connected();
    void disconnected();
    void readData();

signals:
    void engineSensorsDataSent(const QByteArray& data);
    void connEnable();
    void connDisable();

private:
    QTcpSocket *socket;
    QTimer *reconnectTimer;
    QSettings *conSettings;
    QByteArray buffer; // Буфер для хранения данных

    QString droneIP = "localhost";
    quint16 dronePort = 8002;
};

#endif // CLIENT_H
