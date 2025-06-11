#include "ListOfLimitsWidget.h"

#include <QLineEdit>
#include <QCheckBox>
#include "qdebug.h"
#include "qpushbutton.h"
#include <QIntValidator>

#include "Tools/CollapsibleGroupBox.h"
#include "Exchange/Protocols/SensorSettingsManager.h"
#include "DetailingLimitsWidget.h"
#include "qscrollarea.h"


ListOfLimitsWidget::ListOfLimitsWidget(QWidget *parent)
    : QWidget{parent}
    ,framesVBLt(new QVBoxLayout())
{
    setWindowTitle("Список датчиков");
    setMinimumWidth(700);
    framesVBLt->setContentsMargins(0, 0, 0, 0);
    framesVBLt->setSpacing(5);  // небольшой фиксированный отступ между элементами
    setLayout(framesVBLt);
}

void ListOfLimitsWidget::addNewFrame(std::shared_ptr<BaseProtocol> frame)
{

    CollapsibleGroupBox *frameGroupBox = new CollapsibleGroupBox(this);
    frameGroupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    frameGroupBox->setTitle(frame->nameFrame);

    for (auto &it : frame->orderedNames){
        std::shared_ptr<SensorData> fieldData = std::make_shared<SensorData>(frame->fields[it]);

        auto frameShared = frame; // shared_ptr для продления жизни frame
        std::string sensorName = it;  // копия имени сенсора
        std::shared_ptr<SensorData> fieldDataPtr(fieldData);

        if (SensorSettingsManager::loadSensor(org, app, it.data(), *fieldData)) {
            qDebug() << &it << ":" << fieldData->val
                     << "(" << fieldData->limit->min << "-" << fieldData->limit->max << ")";
        }

        QHBoxLayout *hBoxLt = new QHBoxLayout();
        hBoxLt->setContentsMargins(0, 0, 0, 0);
        hBoxLt->setSpacing(5);  // небольшой фиксированный отступ между элементами
        QLabel *nameField = new QLabel(it.data(), frameGroupBox);
        nameField->setMinimumWidth(250);
        hBoxLt->addWidget(nameField);
        hBoxLt->addWidget(new QLabel("Min: ", frameGroupBox));
        QLineEdit *minTxtEdt = new QLineEdit(frameGroupBox);
        minTxtEdt->setValidator(new QIntValidator);
        minTxtEdt->setText(QString::number(fieldData->limit->min));
        connect(minTxtEdt, &QLineEdit::textChanged, [&it, minTxtEdt, &fieldData, this](){
            bool ok = false;
            int value = minTxtEdt->text().toInt(&ok);
            if (ok) {
                fieldData->limit->min = value;
                SensorSettingsManager::saveSensor(org, app, it.data(), *fieldData);
            }
        });
        hBoxLt->addWidget(minTxtEdt);

        hBoxLt->addWidget(new QLabel("Max: ", frameGroupBox));
        QLineEdit *maxTxtEdt = new QLineEdit(frameGroupBox);
        maxTxtEdt->setValidator(new QIntValidator);
        maxTxtEdt->setText(QString::number(fieldData->limit->max));
        connect(maxTxtEdt, &QLineEdit::textChanged, [&it, maxTxtEdt, &fieldData, this](){
            bool ok = false;
            int value = maxTxtEdt->text().toInt(&ok);
            if (ok) {
            fieldData->limit->max = value;
                SensorSettingsManager::saveSensor(org, app, it.data(), *fieldData);
            }
        });
        hBoxLt->addWidget(maxTxtEdt);

        frameGroupBox->addLayout(hBoxLt);
        minTxtEdt->setMinimumWidth(150);
        maxTxtEdt->setMinimumWidth(150);

        QCheckBox *checkBox = new QCheckBox("Детал.", this);
        checkBox->setChecked(fieldData->useDetalaizedLimits);

        connect(checkBox, &QCheckBox::toggled, [frameShared, fieldDataPtr](bool checked) {
            qDebug() << "Checkbox state changed to:" << checked;
            fieldDataPtr->useDetalaizedLimits = checked;
            qDebug() << "New value in fieldData:" << fieldDataPtr->useDetalaizedLimits;
        });

        hBoxLt->addWidget(checkBox);

        QPushButton *openLimitsDetail(new QPushButton("...", this));
        connect(openLimitsDetail, &QPushButton::clicked, [frameShared, fieldDataPtr, sensorName]() {
            DetailingLimitsWidget *detatlsLimits = new DetailingLimitsWidget(fieldDataPtr, sensorName);
            detatlsLimits->setAttribute(Qt::WA_DeleteOnClose);
            detatlsLimits->show();
        });
        hBoxLt->addWidget(openLimitsDetail);

        hBoxLt->addStretch(); // Занимает свободное пространство
    }
    frameGroupBox->setExpanded(false);
    framesVBLt->addWidget(frameGroupBox, 0, Qt::AlignTop | Qt::AlignLeft);
}
