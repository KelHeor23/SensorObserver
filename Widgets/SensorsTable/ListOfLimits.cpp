#include "ListOfLimits.h"

#include "QHBoxLayout"
#include "qdebug.h"

ListOfLimits::ListOfLimits(EngineSensors::Limits *lim, QWidget *parent)
    : QWidget(parent),
    mainLayout(new QVBoxLayout),
    limits{lim}
{
    setLayout(mainLayout);

    QHBoxLayout *headerLayout = new QHBoxLayout(this);
    headerLayout->addWidget(new QLabel("Датчик"));
    headerLayout->addWidget(new QLabel("Мин"));
    headerLayout->addWidget(new QLabel("Макс"));

    mainLayout->addLayout(headerLayout);

    for (auto &it : EngineSensors::orderedNames)
        addWidgets(it);

    mainLayout->addStretch();
}

void ListOfLimits::addWidgets(std::string_view nameSensor)
{
    QHBoxLayout *row = new QHBoxLayout(this);
    QLabel *name = new QLabel(nameSensor.data());
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

    SensorLimits node = limits->sensorsDataLimits[nameSensor.data()];

    connect(min, &QTextEdit::textChanged, this, [this, &node, min]() {
        bool ok;
        int value = min->toPlainText().toInt(&ok);
        if (ok)
            node.min = value;
        else
            // Обработка ошибки преобразования
            qDebug() << "Ошибка преобразования min";
    });

    connect(max, &QTextEdit::textChanged, this, [this, &node, max]() {
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

    mainLayout->addLayout(row);
}
