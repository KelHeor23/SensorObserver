#ifndef LISTOFLIMITS_H
#define LISTOFLIMITS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

#include "../../Exchange/Protocols/EngineSensors/EngineSensors.h"

class ListOfLimits : public QWidget
{
    Q_OBJECT
public:
    explicit ListOfLimits(EngineSensors::Limits *limits, QWidget *parent = nullptr);

public slots:
    void addWidgets(std::string_view);

private:
    QVBoxLayout *mainLayout;
    EngineSensors::Limits *limits;
};

#endif // LISTOFLIMITS_H
