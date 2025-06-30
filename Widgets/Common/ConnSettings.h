#ifndef CONNSETTINGS_H
#define CONNSETTINGS_H

#include <QtWidgets/QWidget>
#include <QSettings>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

class ConnSettings : public QWidget
{
    Q_OBJECT
public:
    explicit ConnSettings(QWidget *parent = nullptr);

    QString getDroneIP() const;

    quint16 getDronePort() const;

private:
    bool isValidIPAddress(const QString &ip);
    bool isValidIPPort(const QString &port);
    void setDefaultBorders();

signals:

private:
    QVBoxLayout *mainLt;
    QHBoxLayout *adressLt;
    QHBoxLayout *buttonsLt;
    QLineEdit *droneIPledt;
    QLineEdit *dronePortledt;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    QString droneIP = "localhost";
    quint16 dronePort = 8021;

    QSettings *conSettings;
};

#endif // CONNSETTINGS_H
