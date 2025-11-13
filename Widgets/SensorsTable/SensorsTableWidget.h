/**
 * \file SensorsTableWidget.h
 * \brief Главный виджет таблицы датчиков и панелей настроек.
 * \details Формирует группы визуализации для ESC/двигателей/регуляторов/прочих, связывает c SensorsFrames и настройками лимитов.
 */

#ifndef SENSORSTABLEWIDGET_H
#define SENSORSTABLEWIDGET_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QtWidgets/QWidget>
#include <QHBoxLayout>
#endif

#include "DisplayingSensors.h"
#include "Data/Frames/Containers/SensorsFrames.h"
#include "VibrationDirection.h"
/**\class SensorsTableWidget
 * \brief Контейнер визуализации сенсоров и управляющих панелей.
 * \details Формирует группы по фреймам, добавляет подписи/значения и связывает лимиты.
 */

class SensorsTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsTableWidget(std::shared_ptr<SensorsFrames> sensorsManager_t, QWidget *parent = nullptr);

    void readEngineSensorsMsg(uint8_t num, const QByteArray& data);
    void readVoltageRegulatorsMsg(uint8_t num, const QByteArray& data);
    void readOtherSensorsMsg(uint8_t num, const QByteArray& data);

private:
    void engineSensorsVisual();

public:
    QVector<DisplayingSensors *> displayngSensors;

private:
    QHBoxLayout *mainHBoxLt;
    QWidget *placeholderWidget;
    std::shared_ptr<SensorsFrames> sensorsManager;
    QVector<VibrationDirection *> vibrationDirections;
};

#endif // SENSORSTABLEWIDGET_H
