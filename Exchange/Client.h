#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

public slots:
    void connectToServer();
    void connected();
    void disconnected();
    void readData();

private:
    QTcpSocket *socket;
    QTimer *reconnectTimer;
    QByteArray buffer; // Буфер для хранения данных
};

#endif // CLIENT_H
