#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "Exchange/Client.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QCloseEvent>

class MotorControl : public QWidget
{
    Q_OBJECT
public:
    MotorControl(Client *client_t, QWidget *parent = nullptr);

private:
    void addNewMotor(uint8_t num);
    void sendMotorControlMsg(uint8_t num, uint16_t pwm);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Client *client;
    QVBoxLayout *mainLt;
};

#endif // MOTORCONTROL_H
