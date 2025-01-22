#ifndef LISTOFLIMITS_H
#define LISTOFLIMITS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

class ListOfLimits : public QWidget
{
    Q_OBJECT
public:
    explicit ListOfLimits(QWidget *parent = nullptr);

public slots:
    void addWidgets();

private:
    QVBoxLayout *mainLayout;
};

#endif // LISTOFLIMITS_H
