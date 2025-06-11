#ifndef DETAILINGLIMITSWIDGET_H
#define DETAILINGLIMITSWIDGET_H

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Exchange/Protocols/Sensors.h"

class DetailingLimitsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetailingLimitsWidget(std::shared_ptr<SensorData> data, std::string name, QWidget *parent = nullptr);

    explicit DetailingLimitsWidget(QWidget *parent = nullptr) = delete;

public slots:
    void addNewMinMax(size_t);
    void addNewPoint(size_t);

signals:

private:
    std::shared_ptr<SensorData> data_t;
    QVBoxLayout *mainLt;
    QVBoxLayout *fieldsLt;
    QHBoxLayout *buttonsLt;
    QPushButton *addNewMinMaxBtn;
    QPushButton *addNewPointBtn;
};

#endif // DETAILINGLIMITSWIDGET_H
