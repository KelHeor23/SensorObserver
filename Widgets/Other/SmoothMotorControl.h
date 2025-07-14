#ifndef SMOOTHMOTORCONTROL_H
#define SMOOTHMOTORCONTROL_H

#include "Exchange/Client.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QPushButton>
#include <qlineedit.h>

class SmoothMotorControl : public QWidget
{
    Q_OBJECT

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
    void closeEvent(QCloseEvent *event) override;

private:
    Client *client;
    QVBoxLayout *mainLt;

    QVector<ControlsSetting> listOfMinMax;

    static constexpr uint8_t cntMototrs = 8;
};

#endif // SMOOTHMOTORCONTROL_H
