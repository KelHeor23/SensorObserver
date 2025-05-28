#include "ListOfLimitsWidget.h"

#include "Tools/CollapsibleGroupBox.h"
#include "qtextedit.h"

ListOfLimitsWidget::ListOfLimitsWidget(QWidget *parent)
    : QWidget{parent}
    ,framesVBLt(new QVBoxLayout(this))
{
    setMinimumSize(300, 200);  // задайте минимальный размер
}

void ListOfLimitsWidget::addNewFrame(BaseProtocol *frame)
{
    CollapsibleGroupBox *frameGroupBox = new CollapsibleGroupBox(this);

    frameGroupBox->setTitle(frame->nameFrame);

    for (auto it : frame->orderedNames){
        SensorData &fieldData = frame->fields[it];

        QHBoxLayout *hBoxLt = new QHBoxLayout(frameGroupBox);
        hBoxLt->addWidget(new QLabel(it.data(), frameGroupBox));
        hBoxLt->addWidget(new QLabel("Min: ", frameGroupBox));
        QTextEdit *minTxtEdt = new QTextEdit(frameGroupBox);
        connect(minTxtEdt, &QTextEdit::textChanged, [minTxtEdt, &fieldData](){
            bool ok = false;
            QString text = minTxtEdt->toPlainText();
            int value = text.toInt(&ok);
            if (ok) {
                fieldData.limit.min = value;
            }
        });
        hBoxLt->addWidget(minTxtEdt);

        hBoxLt->addWidget(new QLabel("Max: ", frameGroupBox));
        QTextEdit *maxTxtEdt = new QTextEdit(frameGroupBox);
        connect(maxTxtEdt, &QTextEdit::textChanged, [maxTxtEdt, &fieldData](){
            bool ok = false;
            QString text = maxTxtEdt->toPlainText();
            int value = text.toInt(&ok);
            if (ok) {
                fieldData.limit.max = value;
            }
        });
        hBoxLt->addWidget(maxTxtEdt);

        frameGroupBox->addLayout(hBoxLt);
    }
    framesVBLt->addWidget(frameGroupBox);
}
