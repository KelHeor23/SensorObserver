#include "ListOfLimitsWidget.h"

#include <QLineEdit>

#include "Tools/CollapsibleGroupBox.h"

ListOfLimitsWidget::ListOfLimitsWidget(QWidget *parent)
    : QWidget{parent}
    ,framesVBLt(new QVBoxLayout(this))
{
    setWindowTitle("Список датчиков");
    setMinimumWidth(700);
    framesVBLt->setContentsMargins(0, 0, 0, 0);
    framesVBLt->setSpacing(5);  // небольшой фиксированный отступ между элементами
}

void ListOfLimitsWidget::addNewFrame(std::shared_ptr<BaseProtocol> frame)
{
    CollapsibleGroupBox *frameGroupBox = new CollapsibleGroupBox(this);
    frameGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    frameGroupBox->setTitle(frame->nameFrame);

    for (auto it : frame->orderedNames){
        SensorData &fieldData = frame->fields[it];

        QHBoxLayout *hBoxLt = new QHBoxLayout(frameGroupBox);
        hBoxLt->setContentsMargins(0, 0, 0, 0);
        hBoxLt->setSpacing(5);  // небольшой фиксированный отступ между элементами
        QLabel *nameField = new QLabel(it.data(), frameGroupBox);
        nameField->setMinimumWidth(200);
        hBoxLt->addWidget(nameField);
        hBoxLt->addWidget(new QLabel("Min: ", frameGroupBox));
        QLineEdit *minTxtEdt = new QLineEdit(frameGroupBox);
        connect(minTxtEdt, &QLineEdit::textChanged, [minTxtEdt, &fieldData](){
            bool ok = false;
            int value = minTxtEdt->text().toInt(&ok);
            if (ok) {
                fieldData.limit.min = value;
            }
        });
        hBoxLt->addWidget(minTxtEdt);

        hBoxLt->addWidget(new QLabel("Max: ", frameGroupBox));
        QLineEdit *maxTxtEdt = new QLineEdit(frameGroupBox);
        connect(maxTxtEdt, &QLineEdit::textChanged, [maxTxtEdt, &fieldData](){
            bool ok = false;
            int value = maxTxtEdt->text().toInt(&ok);
            if (ok) {
                fieldData.limit.max = value;
            }
        });
        hBoxLt->addWidget(maxTxtEdt);

        frameGroupBox->addLayout(hBoxLt);
        minTxtEdt->setMinimumWidth(150);
        maxTxtEdt->setMinimumWidth(150);
    }
    frameGroupBox->setExpanded(false);
    framesVBLt->addWidget(frameGroupBox, 0, Qt::AlignTop | Qt::AlignLeft);
}
