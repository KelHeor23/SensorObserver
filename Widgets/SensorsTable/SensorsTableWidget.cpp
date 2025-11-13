/**
 * \file SensorsTableWidget.cpp
 * \brief Реализация таблицы датчиков и построителя панелей.
 * \details Создаёт группы, добавляет метки сенсоров, связывает лимиты, строит секцию «Датчики двигателя».
 */

#include "SensorsTableWidget.h"
#include "Data/Frames/Frames.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <iostream>
#include <ostream>
#endif
/** \brief Собирает интерфейс: создаёт группы фреймов и наполняет их сенсорами. */

SensorsTableWidget::SensorsTableWidget(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent)
    : QWidget{parent}
    , mainHBoxLt(new QHBoxLayout())
    , placeholderWidget(new QWidget(this))
    , sensorsManager(sensorsManager_t)
{
    setLayout(mainHBoxLt);

    for (int i = 0; i < 4; i++){
        vibrationDirections.append(new VibrationDirection(this));
    }

    for (int i = 0; i < 8; i++){
        displayngSensors.append(new DisplayingSensors(sensorsManager, this));
        displayngSensors.last()->addNewDataLabels(sensorsManager->getFrames()[VOLTAGE_REGULATORS]->orderedNames);
        displayngSensors.last()->addNewDataLabels(sensorsManager->getFrames()[ENGINE]->orderedNames);
        displayngSensors.last()->addNewDataLabels(sensorsManager->getFrames()[ESC_FRAME1]->orderedNames);
        displayngSensors.last()->addNewDataLabels(sensorsManager->getFrames()[ESC_FRAME2]->orderedNames);
        displayngSensors.last()->addNewDataLabels(sensorsManager->getFrames()[ESC_FRAME3]->orderedNames);
        displayngSensors.last()->addNewDataLabels(sensorsManager->getFrames()[OTHER_SENSROS]->orderedNames);
        displayngSensors.last()->linkLimitsSensorsFrames(sensorsManager);
    }

    // Формирование визуализации датчиков двигателей
    engineSensorsVisual();
}
/** \brief Строит визуализацию секции «Датчики двигателя». */

void SensorsTableWidget::engineSensorsVisual()
{
    QVBoxLayout *engineVBoxLt;
    QHBoxLayout *engineSensorsHBLt;

    for (int i = 0; i < vibrationDirections.size(); i++){
        engineVBoxLt = new QVBoxLayout();
        engineSensorsHBLt = new QHBoxLayout();
        vibrationDirections[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        engineVBoxLt->addWidget(vibrationDirections[i]);
        engineSensorsHBLt->addWidget(displayngSensors[i * 2]);
        engineSensorsHBLt->addWidget(displayngSensors[i * 2 + 1]);
        engineVBoxLt->addLayout(engineSensorsHBLt);
        mainHBoxLt->addLayout(engineVBoxLt);
    }
}

void SensorsTableWidget::readEngineSensorsMsg(uint8_t num, const QByteArray &data)
{
    std::string_view sv(data.constData() , data.size());

    if (num >= 8)
    {
        std::cerr << "readEngineSensorsMsg" << std::endl;
        return;
    }

    displayngSensors[num]->setSensorsData(ENGINE, sv, num);

    auto frame = displayngSensors[num]->getSensorManager()->getFrames()[ENGINE]->fields;

    if (num % 2 == 0) {
        vibrationDirections[num / 2]->update(frame["Амплитуда биения"]->val / 1000, frame["Угол биения"]->val);
    }
}

void SensorsTableWidget::readVoltageRegulatorsMsg(uint8_t num, const QByteArray &data)
{
    std::string_view sv(data.constData() , data.size());

    if (num >= 8)
    {
        std::cerr << "readVoltageRegulatorsMsg" << std::endl;
        return;
    }

    displayngSensors[num]->setSensorsData(VOLTAGE_REGULATORS, sv, num);
}

void SensorsTableWidget::readOtherSensorsMsg(uint8_t num, const QByteArray &data)
{
    std::string_view sv(data.constData() , data.size());

    if (num >= 8)
    {
        std::cerr << "readOtherSensorsMsg" << std::endl;
        return;
    }

    displayngSensors[num]->setSensorsData(OTHER_SENSROS, sv, num);
}
