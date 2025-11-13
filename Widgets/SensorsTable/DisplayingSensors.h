/**
 * \file DisplayingSensors.h
 * \brief Виджет отображения набора сенсоров для одного фрейма.
 * \details Отрисовывает подписи/значения, подсветку по лимитам, предоставляет переход к редактированию настроек сенсора.
 */

#ifndef DISPLAYINGSENSORS_H
#define DISPLAYINGSENSORS_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#endif

#include "Data/Frames/Containers/SensorsFrames.h"
#include "Tools/ColorProgressBar.h"
/**\class DisplayingSensors
 * \brief Панель отображения значений сенсоров одного фрейма.
 * \details Содержит подписи, значения и кнопки открытия настроек; поддерживает подсветку по лимитам.
 */

class DisplayingSensors : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayingSensors(std::shared_ptr<SensorsFrames> sensorManager_t, QWidget *parent = nullptr);

    void setSensorsData(FrameTypes type, std::string_view data, int16_t node_id);
    /** \brief Добавляет подписи/поля для новых сенсоров указанного фрейма. */
    void addNewDataLabels(std::vector<SensorName> &list);
    /** \brief Связывает панель с менеджером фреймов и лимитов для подсветки. */

    void linkLimitsSensorsFrames(std::shared_ptr<SensorsFrames>);
    void linkFrame(FrameTypes type, std::shared_ptr<SensorsFrames> target);

    std::shared_ptr<SensorsFrames> getSensorManager() const;

public slots:
    void addWidgets(std::string_view);
    //void checkRangeValues(QLabel *, std::shared_ptr<SensorData> field);
    void checkRangeValues(ColorProgressBar *, std::shared_ptr<SensorData> field);

private:
    QGridLayout *mainLayout;
    std::shared_ptr<SensorsFrames> sensorManager;
    std::unordered_map<QString, QLabel *> sensorsDataLabels;
    std::unordered_map<QString, ColorProgressBar *> sensorsColorProgressBarDataLabels;
};

#endif // DISPLAYINGSENSORS_H
