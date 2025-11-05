#ifndef DATAREADER_H
#define DATAREADER_H

#include "Exchange/Client.h"
#include "Widgets/SensorsTable/SensorsTableWidget.h"

class DataReader : public QObject
{
    Q_OBJECT
public:
    DataReader() = delete;
    DataReader(Client *_client, SensorsTableWidget *_sensorsTableWdgt);

public slots:
    void parseMsg(const QByteArray& data);

private:
    Client *client;
    SensorsTableWidget  *sensorsTableWdgt;
};

#endif // DATAREADER_H
