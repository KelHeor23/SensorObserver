/**
 * \file MotorControl.h
 * \brief Ручное управление PWM моторов по отдельности.
 * \details Добавляет элементы управления для каждого мотора и отправляет команды по сети.
 */

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "Exchange/Client.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QWidget>
#include <QVBoxLayout>
#include <QCloseEvent>
#endif
/**\class MotorControl
 * \brief Панель ручного управления PWM отдельных моторов.
 * \details Для каждого мотора добавляет набор контролов и отправляет команды в бортовой модуль.
 */

class MotorControl : public QWidget
{
    Q_OBJECT
public:
    MotorControl(Client *client_t, QWidget *parent = nullptr);

private:
    /** \brief Добавляет блок управления для мотора с заданным индексом. */
    void addNewMotor(uint8_t num);
    /** \brief Отправляет команду MOTOR_CONTROL с PWM для выбранного мотора. */
    void sendMotorControlMsg(uint8_t num, uint16_t pwm);

protected:
    /** \brief При закрытии окна сбрасывает PWM всех моторов на безопасное значение и разрешает закрытие. */
    void closeEvent(QCloseEvent *event) override;

private:
    Client *client;
    QVBoxLayout *mainLt;
};

#endif // MOTORCONTROL_H
