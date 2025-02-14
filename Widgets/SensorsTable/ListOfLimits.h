#ifndef LISTOFLIMITS_H
#define LISTOFLIMITS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

#include "../../Exchange/Protocols/Sensors.h"

using HashLimits = std::unordered_map<SensorName, SensorLimits>;

class ListOfLimits : public QWidget
{
    Q_OBJECT
public:
    explicit ListOfLimits(QWidget *parent = nullptr);

    std::shared_ptr<HashLimits> getSensorsDataLimits() const;

public slots:
    void addWidget(std::string_view);

    void addNewLimits(std::vector<SensorName> &list);

private:
    QVBoxLayout *mainLayout;

    std::shared_ptr<HashLimits> sensorsDataLimits;
};

#endif // LISTOFLIMITS_H
