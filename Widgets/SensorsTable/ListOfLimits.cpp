#include "ListOfLimits.h"

#include "QHBoxLayout"

ListOfLimits::ListOfLimits(QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout)
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QHBoxLayout *headerLayout = new QHBoxLayout(this);
    headerLayout->addWidget(new QLabel("Датчик"));
    headerLayout->addWidget(new QLabel("Мин"));
    headerLayout->addWidget(new QLabel("Макс"));

    mainLayout->addLayout(headerLayout);

    // Добавление кнопки для добавления виджетов
    QPushButton *button = new QPushButton("Добавить виджеты");
    connect(button, &QPushButton::clicked, this, &ListOfLimits::addWidgets);
    mainLayout->addWidget(button);
}

void ListOfLimits::addWidgets()
{
    QHBoxLayout *row = new QHBoxLayout(this);;
    row->addWidget(new QLabel("Имя"));
    row->addWidget(new QTextEdit());
    row->addWidget(new QTextEdit());

    mainLayout->insertLayout(mainLayout->count() - 1, row);
}
