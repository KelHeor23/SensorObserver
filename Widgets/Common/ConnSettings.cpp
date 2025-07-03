#include "ConnSettings.h"
#include "qlabel.h"
#include <QRegularExpression>

ConnSettings::ConnSettings(QWidget *parent)
    : QWidget{parent}
    , mainLt(new QVBoxLayout)
    , adressLt(new QHBoxLayout)
    , buttonsLt(new QHBoxLayout)
    , droneIPledt(new QLineEdit(this))
    , dronePortledt(new QLineEdit(this))
    , okBtn(new QPushButton("Ok", this))
    , cancelBtn(new QPushButton("Cancel", this))
    , conSettings(new QSettings("settings", "conSettings", this))
{
    setWindowTitle("Настройка подключения");

    adressLt->addWidget(new QLabel("IP:", this));
    adressLt->addWidget(droneIPledt);
    adressLt->addWidget(new QLabel("port:", this));
    adressLt->addWidget(dronePortledt);

    mainLt->addLayout(adressLt);

    buttonsLt->addWidget(okBtn);
    buttonsLt->addWidget(cancelBtn);

    connect(okBtn, &QPushButton::clicked, this, &ConnSettings::ok);
    connect(cancelBtn, &QPushButton::clicked,  this, &ConnSettings::cancel);

    mainLt->addLayout(buttonsLt);
    setLayout(mainLt);

    loadSettings();
}

QString ConnSettings::getDroneIP() const
{
    return droneIP;
}

quint16 ConnSettings::getDronePort() const
{
    return dronePort;
}

bool ConnSettings::isValidIPAddress(const QString &ip)
{
    QRegularExpression regex("^(localhost|((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))$");
    return regex.match(ip).hasMatch(); // Проверка соответствия
}

bool ConnSettings::isValidIPPort(const QString &port)
{
    bool succes = true;
    int port_t = port.toInt(&succes);
    return succes && (port_t >= 0 && port_t <= 65535);
}

void ConnSettings::setDefaultBorders()
{
    droneIPledt->setStyleSheet("QLineEdit { border: 0px solid black }");
    dronePortledt->setStyleSheet("QLineEdit { border: 0px solid black }");
}

void ConnSettings::saveSettings()
{
    conSettings->setValue("droneIP", droneIP);
    conSettings->setValue("dronePort", dronePort);
}

void ConnSettings::loadSettings()
{
    droneIP    = conSettings->value("droneIP", "localhost").toString();
    dronePort  = conSettings->value("dronePort", 8021).toInt();

    droneIPledt->setText(droneIP);
    dronePortledt->setText(QString::number(dronePort));
}

void ConnSettings::ok()
{
    bool isFalse = false;

    if (!isValidIPAddress(droneIPledt->text())){
        droneIPledt->setStyleSheet("QLineEdit { border: 2px solid red; }");
        isFalse = true;
    }

    if (!isValidIPPort(dronePortledt->text())){
        dronePortledt->setStyleSheet("QLineEdit { border: 2px solid red; }");
        isFalse = true;
    }

    if (!isFalse) {
        droneIP    = droneIPledt->text();
        dronePort  = dronePortledt->text().toInt();

        setDefaultBorders();
        saveSettings();

        emit newConnSettings();
        this->close();
    }
}

void ConnSettings::cancel()
{
    loadSettings();
    setDefaultBorders();
}


