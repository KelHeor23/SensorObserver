/**
 * \file DetailingLimitsWidget.h
 * \brief Детальная настройка порогов/цветов для одного сенсора.
 * \details Добавление/удаление точек порогов, выбор цвета и сохранение изменений через SensorSettingsManager.
 */

#ifndef DETAILINGLIMITSWIDGET_H
#define DETAILINGLIMITSWIDGET_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#endif

#include "Data/Frames/Containers/Sensors.h"
/**\class DetailingLimitsWidget
 * \brief Детальная настройка порогов: точки (value+color), добавление/удаление.
 * \details Сохраняет через SensorSettingsManager при закрытии.
 */

class DetailingLimitsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetailingLimitsWidget(std::shared_ptr<SensorData> data, QString name, QWidget *parent = nullptr);

    explicit DetailingLimitsWidget(QWidget *parent = nullptr) = delete;

public slots:
    void addNewMinMax(size_t);
    void addNewPoint(size_t);

protected:
    void closeEvent(QCloseEvent *event) override;

signals:

private:
    std::shared_ptr<SensorData> data_t;
    QString sensorName;
    QVBoxLayout *mainLt;
    QVBoxLayout *fieldsLt;
    QHBoxLayout *buttonsLt;
    QPushButton *addNewMinMaxBtn;
    QPushButton *addNewPointBtn;
};

#endif // DETAILINGLIMITSWIDGET_H
