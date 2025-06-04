#ifndef LISTOFLIMITSWIDGET_H
#define LISTOFLIMITSWIDGET_H

#include <QtWidgets/QWidget>
#include <QVBoxLayout>

#include "Exchange/Protocols/Base.h"

class ListOfLimitsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListOfLimitsWidget(QWidget *parent = nullptr);

    void addNewFrame(std::shared_ptr<BaseProtocol> frame);
signals:

private:
    QVBoxLayout *framesVBLt;

    const QString org = "Breez";
    const QString app = "SensorApp";
};

#endif // LISTOFLIMITSWIDGET_H
