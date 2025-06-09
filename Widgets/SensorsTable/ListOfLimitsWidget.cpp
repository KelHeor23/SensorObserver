#include "ListOfLimitsWidget.h"

#include <QLineEdit>
#include <QCheckBox>
#include "qdebug.h"
#include "qpushbutton.h"

#include "Tools/CollapsibleGroupBox.h"
#include "Exchange/Protocols/SensorSettingsManager.h"
#include "DetailingLimitsWidget.h"
#include "qscrollarea.h"


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
    CollapsibleGroupBox *frameGroupBox = new CollapsibleGroupBox();
    frameGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    frameGroupBox->setTitle(frame->nameFrame);

    for (auto &it : frame->orderedNames){
        SensorData &fieldData = frame->fields[it];

        if (SensorSettingsManager::loadSensor(org, app, it.data(), fieldData)) {
            qDebug() << &it << ":" << fieldData.val
                     << "(" << fieldData.limit->min << "-" << fieldData.limit->max << ")";
        }

        QHBoxLayout *hBoxLt = new QHBoxLayout();
        hBoxLt->setContentsMargins(0, 0, 0, 0);
        hBoxLt->setSpacing(5);  // небольшой фиксированный отступ между элементами
        QLabel *nameField = new QLabel(it.data(), frameGroupBox);
        nameField->setMinimumWidth(250);
        hBoxLt->addWidget(nameField);
        hBoxLt->addWidget(new QLabel("Min: ", frameGroupBox));
        QLineEdit *minTxtEdt = new QLineEdit(frameGroupBox);
        minTxtEdt->setText(QString::number(fieldData.limit->min));
        connect(minTxtEdt, &QLineEdit::textChanged, [&it, minTxtEdt, &fieldData, this](){
            bool ok = false;
            int value = minTxtEdt->text().toInt(&ok);
            if (ok) {
                fieldData.limit->min = value;
                SensorSettingsManager::saveSensor(org, app, it.data(), fieldData);
            }
        });
        hBoxLt->addWidget(minTxtEdt);

        hBoxLt->addWidget(new QLabel("Max: ", frameGroupBox));
        QLineEdit *maxTxtEdt = new QLineEdit(frameGroupBox);
        maxTxtEdt->setText(QString::number(fieldData.limit->max));
        connect(maxTxtEdt, &QLineEdit::textChanged, [&it, maxTxtEdt, &fieldData, this](){
            bool ok = false;
            int value = maxTxtEdt->text().toInt(&ok);
            if (ok) {
                fieldData.limit->max = value;
                SensorSettingsManager::saveSensor(org, app, it.data(), fieldData);
            }
        });
        hBoxLt->addWidget(maxTxtEdt);

        frameGroupBox->addLayout(hBoxLt);
        minTxtEdt->setMinimumWidth(150);
        maxTxtEdt->setMinimumWidth(150);

        QCheckBox *checkBox = new QCheckBox("Детал.", this);
        checkBox->setChecked(fieldData.useDetalaizedLimits);
        connect(checkBox, &QCheckBox::toggled, [&fieldData](int checked){
            fieldData.useDetalaizedLimits = (checked == Qt::Checked);
        });

        hBoxLt->addWidget(checkBox);

        QPushButton *openLimitsDetail(new QPushButton("...", this));
        connect(openLimitsDetail, &QPushButton::clicked, [&fieldData](){
            DetailingLimitsWidget *detatlsLimits(new DetailingLimitsWidget(fieldData));
            detatlsLimits->setAttribute(Qt::WA_DeleteOnClose);
            detatlsLimits->show();
        });
        hBoxLt->addWidget(openLimitsDetail);

        hBoxLt->addStretch(); // Занимает свободное пространство
    }
    frameGroupBox->setExpanded(false);
    framesVBLt->addWidget(frameGroupBox, 0, Qt::AlignTop | Qt::AlignLeft);
}
