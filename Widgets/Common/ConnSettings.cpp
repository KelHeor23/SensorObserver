/**
 * \file ConnSettings.cpp
 * \brief Реализация виджета ConnSettings.
 * \details Создаёт поля ввода IP/порта, валидирует значения, читает/пишет QSettings и эмитирует сигнал newConnSettings.
 */

#include "ConnSettings.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "qlabel.h"
#include <QRegularExpression>
#endif
/** \brief Создаёт поля ввода IP/порта, кнопки и загружает сохранённые значения. */

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
/** \brief Убирает подсветку ошибок и восстанавливает стандартные рамки у полей ввода. */

void ConnSettings::setDefaultBorders()
{
    droneIPledt->setStyleSheet("QLineEdit { border: 0px solid black }");
    dronePortledt->setStyleSheet("QLineEdit { border: 0px solid black }");
}
/** \brief Записывает значения полей в QSettings ("droneIP", "dronePort"). */

void ConnSettings::saveSettings()
{
    conSettings->setValue("droneIP", droneIP);
    conSettings->setValue("dronePort", dronePort);
}
/** \brief Читает значения из QSettings и заполняет поля ввода. */

void ConnSettings::loadSettings()
{
    droneIP    = conSettings->value("droneIP", "localhost").toString();
    dronePort  = conSettings->value("dronePort", 8021).toInt();

    droneIPledt->setText(droneIP);
    dronePortledt->setText(QString::number(dronePort));
}
/**
 * \brief Обработчик кнопки Ok.
 * \details Валидирует IP и порт (через QRegularExpression), при успехе сохраняет значения,
 * эмитирует сигнал newConnSettings() и закрывает диалог.
 */

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
/** \brief Сбрасывает изменения, перезагружает сохранённые значения и возвращает стандартные рамки. */

void ConnSettings::cancel()
{
    loadSettings();
    setDefaultBorders();
}
