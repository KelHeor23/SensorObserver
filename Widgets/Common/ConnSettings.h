/**
 * \file ConnSettings.h
 * \brief Виджет настроек подключения (IP/порт).
 * \details Позволяет задать IP/hostname и порт подключения к дрону; хранит значения в QSettings и уведомляет об изменении.
 */

#ifndef CONNSETTINGS_H
#define CONNSETTINGS_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QtWidgets/QWidget>
#include <QSettings>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#endif
/**\class ConnSettings
 * \brief Диалог настроек подключения к бортовому модулю.
 * \details Содержит поля ввода IP/порта, кнопки Ok/Cancel и сохраняет значения в QSettings.
 */

class ConnSettings : public QWidget
{
    Q_OBJECT
public:
    explicit ConnSettings(QWidget *parent = nullptr);
    /** \return Текущее значение IP/hostname из поля ввода. */

    QString getDroneIP() const;
    /** \return Текущее значение порта из поля ввода. */

    quint16 getDronePort() const;

private:
    bool isValidIPAddress(const QString &ip);
    bool isValidIPPort(const QString &port);
    /** \brief Сбрасывает подсветку/рамки валидации у полей ввода. */
    void setDefaultBorders();
    /** \brief Сохраняет IP/порт в QSettings (ключи "droneIP" и "dronePort"). */
    void saveSettings();
    /** \brief Загружает IP/порт из QSettings в поля ввода. */
    void loadSettings();

public slots:
    void ok();
    /** \brief Отменяет изменения: перезагружает сохранённые настройки и закрывает диалог. */
    void cancel();

signals:
    void newConnSettings();

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
