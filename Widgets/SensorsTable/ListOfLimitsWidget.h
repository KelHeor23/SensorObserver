/**
 * \file ListOfLimitsWidget.h
 * \brief Список лимитов сенсора (краткий вид).
 * \details Позволяет просматривать/открывать детальную настройку порогов и цветов для выбранного сенсора.
 */

#ifndef LISTOFLIMITSWIDGET_H
#define LISTOFLIMITSWIDGET_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#endif

#include "Data/Frames/Containers/Base.h"
/**\class ListOfLimitsWidget
 * \brief Краткий список порогов/лимитов для сенсора.
 * \details Позволяет открыть детальную настройку и применить изменения.
 */

class ListOfLimitsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListOfLimitsWidget(QWidget *parent = nullptr);

    void addNewFrame(std::shared_ptr<BaseProtocol> frame);
signals:

private:
    QVBoxLayout *framesVBLt;
};

#endif // LISTOFLIMITSWIDGET_H
