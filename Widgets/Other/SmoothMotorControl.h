/**
 * \file SmoothMotorControl.h
 * \brief Виджет плавного управления моторами.
 * \details Задаёт min/max PWM и время нарастания, управляет инкрементаторами и отправляет команды.
 */

#ifndef SMOOTHMOTORCONTROL_H
#define SMOOTHMOTORCONTROL_H

#include "Exchange/Client.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QWidget>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QPushButton>
#include <qlineedit.h>
#endif
/**\class SmoothMotorControl
 * \brief Плавное управление моторами (min→max за заданное время).
 * \details Позволяет настроить диапазон PWM и длительность для каждого мотора.
 */

class SmoothMotorControl : public QWidget
{
    Q_OBJECT
    /** \struct ControlsSetting
 * \brief Набор виджетов/параметров для одного мотора: поля min/max/timer и кнопки.
 */

    struct ControlsSetting{
        QLineEdit *minPwm;
        QLineEdit *maxPwm;
        QLineEdit *timer;
    };

public:
    SmoothMotorControl(Client *client_t, QWidget *parent = nullptr);

private:
    void addNewMotor(uint8_t num);
    void sendMotorControlMsg(uint8_t num, uint16_t pwm);
    void smoothControl(QPushButton *stopBtn, uint8_t num, uint16_t minPwm, uint16_t maxPwm, uint16_t timer);

private slots:
    void sendAllMotorsControlMsg();

protected:
    /** \brief При закрытии окна отправляет безопасный PWM всем моторам и разрешает закрытие. */
    void closeEvent(QCloseEvent *event) override;

private:
    Client *client;
    QVBoxLayout *mainLt;

    QVector<ControlsSetting> listOfMinMax;

    static constexpr uint8_t cntMototrs = 8;
};

#endif // SMOOTHMOTORCONTROL_H
