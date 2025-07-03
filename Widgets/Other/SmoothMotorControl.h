#ifndef SMOOTHMOTORCONTROL_H
#define SMOOTHMOTORCONTROL_H

#include "Exchange/Client.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QCloseEvent>

class SmoothMotorControl : public QWidget
{
    Q_OBJECT
public:
    SmoothMotorControl(Client *client_t, QWidget *parent = nullptr);

private:
    void addNewMotor(uint8_t num);
    void sendMotorControlMsg(uint8_t num, uint16_t pwm);
    void smoothControl(uint8_t num, uint16_t minPwm, uint16_t maxPwm, uint16_t timer);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Client *client;
    QVBoxLayout *mainLt;
};

#endif // SMOOTHMOTORCONTROL_H
