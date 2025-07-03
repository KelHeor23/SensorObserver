#include "SmoothMotorControl.h"
#include "Tools/ValueIncrementer.h"

#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>
#include <QThread>

SmoothMotorControl::SmoothMotorControl(Client *client_t, QWidget *parent)
    : QWidget{parent}
    , client(client_t)
    , mainLt(new QVBoxLayout)
{
    setWindowTitle("Плавное управление двигателями");
    setLayout(mainLt);

    for (uint8_t i = 0; i < 8; i++)
        addNewMotor(i);
}

void SmoothMotorControl::addNewMotor(uint8_t num)
{
    QHBoxLayout *dataLt = new QHBoxLayout;

    QLabel *name = new QLabel(this);
    name->setText("Двигатель " + QString::number(num) + ":");
    dataLt->addWidget(name);

    QLabel *minLbl = new QLabel(this);
    minLbl->setText("Min: ");
    dataLt->addWidget(minLbl);

    QLineEdit* minPwmLnEdt = new QLineEdit(this);
    minPwmLnEdt->setText(QString::number(900));
    minPwmLnEdt->setValidator(new QIntValidator(this)); // разрешит ввод только целых
    dataLt->addWidget(minPwmLnEdt);

    QLabel *maxLbl = new QLabel(this);
    maxLbl->setText("Max: ");
    dataLt->addWidget(maxLbl);

    QLineEdit* maxPwmLnEdt = new QLineEdit(this);
    maxPwmLnEdt->setText(QString::number(900));
    maxPwmLnEdt->setValidator(new QIntValidator(this)); // разрешит ввод только целых
    dataLt->addWidget(maxPwmLnEdt);

    QLabel *timeLbl = new QLabel(this);
    timeLbl->setText("Time: ");
    dataLt->addWidget(timeLbl);

    QLineEdit* timeLnEdt = new QLineEdit(this);
    timeLnEdt->setText(QString::number(0));
    timeLnEdt->setValidator(new QIntValidator(this)); // разрешит ввод только целых
    dataLt->addWidget(timeLnEdt);

    QPushButton *sendBtn = new QPushButton("Задать", this);
    connect(sendBtn, &QPushButton::clicked, [num, minPwmLnEdt, this, maxPwmLnEdt, timeLnEdt](){
        bool isGood = true;

        uint16_t tempMin = minPwmLnEdt->text().toUInt();
        if (tempMin >= 900 && tempMin <= 2000){
            minPwmLnEdt->setStyleSheet("QLineEdit { border: 0px solid black }");
        } else {
            minPwmLnEdt->setStyleSheet("QLineEdit { border: 2px solid red; }");
            isGood = false;
        }

        uint16_t tempMax = maxPwmLnEdt->text().toUInt();
        if (tempMax >= 900 && tempMax <= 2000){
            maxPwmLnEdt->setStyleSheet("QLineEdit { border: 0px solid black }");
        } else {
            maxPwmLnEdt->setStyleSheet("QLineEdit { border: 2px solid red; }");
            isGood = false;
        }

        uint16_t tempTime = timeLnEdt->text().toUInt();
        if (isGood) {
            smoothControl(num, tempMin, tempMax, tempTime);
        }
    });
    dataLt->addWidget(sendBtn);

    QPushButton *stopBtn = new QPushButton("Стоп", this);
    connect(stopBtn, &QPushButton::clicked, [num, minPwmLnEdt, this](){
        minPwmLnEdt->setStyleSheet("QLineEdit { border: 0px solid black }");
        sendMotorControlMsg(num, 900);
        minPwmLnEdt->setText(QString::number(900));
    });
    dataLt->addWidget(stopBtn);

    mainLt->addLayout(dataLt);
}

void SmoothMotorControl::sendMotorControlMsg(uint8_t num, uint16_t pwm)
{
    Msg::MotorControlMsg msg;
    msg.comand = Msg::Command::MOTOR_CONTROL;
    msg.motorNum = num;
    msg.pwm = pwm;
    QByteArray byteArray(reinterpret_cast<const char*>(&msg), sizeof( Msg::MotorControlMsg));
    client->sendMsg(byteArray);
}

void SmoothMotorControl::smoothControl(uint8_t num, uint16_t minPwm, uint16_t maxPwm, uint16_t timer)
{
    ValueIncrementer *incrementer = new ValueIncrementer(minPwm, maxPwm, timer);

    connect(incrementer, &ValueIncrementer::valueChanged, [num, this](double val){
        sendMotorControlMsg(num, val);
    });
    connect(incrementer, &ValueIncrementer::finished, [incrementer](){
        delete incrementer;
    });

    incrementer->start();
}

void SmoothMotorControl::closeEvent(QCloseEvent *event) {

    event->accept(); // разрешить закрытие
    for (uint8_t num = 0; num < 8; num++)
        sendMotorControlMsg(num, 900);
}
