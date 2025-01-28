#ifndef LISTOFLIMITS_H
#define LISTOFLIMITS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

#include "../../Exchange/Protocols/EngineSensors.h"

class ListOfLimits : public QWidget
{
    Q_OBJECT
public:
    explicit ListOfLimits(EngineSensors &sensors, QWidget *parent = nullptr);

public slots:
    void addWidgets(EngineSensors::NodeSensor &name, int i);

private:
    QVBoxLayout *mainLayout;
};

#endif // LISTOFLIMITS_H
