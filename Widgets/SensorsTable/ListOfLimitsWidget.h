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

    void addNewFrame(BaseProtocol *frame);
signals:

private:
    QVBoxLayout *framesVBLt;
};

#endif // LISTOFLIMITSWIDGET_H
