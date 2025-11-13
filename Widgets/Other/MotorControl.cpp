/**
 * \file MotorControl.cpp
 * \brief Реализация ручного управления моторами.
 * \details Формирует и отправляет кадр MOTOR_CONTROL; при закрытии сбрасывает PWM всех моторов.
 */

#include "MotorControl.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>
#endif
/** \brief Создаёт UI для управления 8 моторами и подключает обработчики. */

MotorControl::MotorControl(Client *client_t, QWidget *parent)
    : QWidget{parent}
    , client(client_t)
    , mainLt(new QVBoxLayout)
{
    setWindowTitle("Управление двигателями");
    setLayout(mainLt);

    for (uint8_t i = 0; i < 8; i++)
        addNewMotor(i);
}

void MotorControl::addNewMotor(uint8_t num)
{
    QHBoxLayout *dataLt = new QHBoxLayout;

    QLabel *name = new QLabel(this);
    name->setText("Двигатель " + QString::number(num) + ":");
    dataLt->addWidget(name);

    QLineEdit* pwmLnEdt = new QLineEdit(this);
    pwmLnEdt->setText(QString::number(900));
    pwmLnEdt->setValidator(new QIntValidator(this)); // разрешит ввод только целых
    dataLt->addWidget(pwmLnEdt);

    QPushButton *sendBtn = new QPushButton("Задать", this);
    connect(sendBtn, &QPushButton::clicked, [num, pwmLnEdt, this](){
        uint16_t temp = pwmLnEdt->text().toUInt();
        if (temp >= 900 && temp <= 2000){
            pwmLnEdt->setStyleSheet("QLineEdit { border: 0px solid black }");
            sendMotorControlMsg(num, temp);
        } else {
            pwmLnEdt->setStyleSheet("QLineEdit { border: 2px solid red; }");
        }
    });
    dataLt->addWidget(sendBtn);

    QPushButton *stopBtn = new QPushButton("Стоп", this);
    connect(stopBtn, &QPushButton::clicked, [num, pwmLnEdt, this](){
        pwmLnEdt->setStyleSheet("QLineEdit { border: 0px solid black }");
        sendMotorControlMsg(num, 900);
        pwmLnEdt->setText(QString::number(900));
    });
    dataLt->addWidget(stopBtn);

    mainLt->addLayout(dataLt);
}
/**
 * \brief Формирует пакет Msg::MotorControlMsg и отправляет через Client.
 * \param[in] num Индекс мотора (0..7).
 * \param[in] pwm Значение PWM (мкс).
 */

void MotorControl::sendMotorControlMsg(uint8_t num, uint16_t pwm)
{
    Msg::MotorControlMsg msg;
    msg.comand = Msg::Command::MOTOR_CONTROL;
    msg.motorNum = num;
    msg.pwm = pwm;
    QByteArray byteArray(reinterpret_cast<const char*>(&msg), sizeof( Msg::MotorControlMsg));
    client->sendMsg(byteArray);
}
/** \brief На закрытие окна отправляет всем моторам PWM=900 (стоп), затем принимает событие. */

void MotorControl::closeEvent(QCloseEvent *event) {

    event->accept(); // разрешить закрытие
    for (uint8_t num = 0; num < 8; num++)
        sendMotorControlMsg(num, 900);
}
