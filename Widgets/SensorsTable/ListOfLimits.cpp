#include "ListOfLimits.h"

#include "QHBoxLayout"
#include "qdebug.h"

ListOfLimits::ListOfLimits(EngineSensors::Limits &limits, QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout)
{
    setLayout(mainLayout);

    QHBoxLayout *headerLayout = new QHBoxLayout(this);
    headerLayout->addWidget(new QLabel("Датчик"));
    headerLayout->addWidget(new QLabel("Мин"));
    headerLayout->addWidget(new QLabel("Макс"));

    mainLayout->addLayout(headerLayout);

    /*for (int i = 0; i < limits.sensorsDataLimits.size(); i++){
        addWidgets(limits.sensorsDataLimits[i], i);
    }*/
    mainLayout->addStretch();
}

void ListOfLimits::addWidgets(SensorLimits &node, int i)
{
    /*QHBoxLayout *row = new QHBoxLayout(this);
    QLabel *name = new QLabel(node.name.name);
    name->setMinimumWidth(150);

    QTextEdit *min = new QTextEdit("0", this);
    if (!min) {
        // Обработка ошибки выделения памяти
        return;
    }
    min->setMaximumHeight(30);

    QTextEdit *max = new QTextEdit("0", this);
    if (!max) {
        delete min; // Удалить min, чтобы избежать утечки памяти
        return;
    }
    max->setMaximumHeight(30);

    connect(min, &QTextEdit::textChanged, this, [this, i, &node, min]() {
        bool ok;
        int value = min->toPlainText().toInt(&ok);
        if (ok)
            node.min = value;
        else
            // Обработка ошибки преобразования
            qDebug() << "Ошибка преобразования min";
    });

    connect(max, &QTextEdit::textChanged, this, [this, i, &node, max]() {
        bool ok;
        int value = max->toPlainText().toInt(&ok);
        if (ok)
            node.max = value;
        else
            // Обработка ошибки преобразования
            qDebug() << "Ошибка преобразования max";
    });

    row->addWidget(name);
    row->addWidget(min);
    row->addWidget(max);

    mainLayout->addLayout(row);*/
}
