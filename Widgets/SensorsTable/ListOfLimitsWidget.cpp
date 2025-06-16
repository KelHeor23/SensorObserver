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

    for (auto &it : frame->orderedNames) {
        std::shared_ptr<SensorData> fieldData = frame->fields[it];

        auto frameShared = frame;
        QString sensorName = QString::fromStdString(it);  // Локальная копия

        if (SensorSettingsManager::loadSensor(it.data(), fieldData)) {
            qDebug() << &it << ":" << fieldData->val
                     << "(" << fieldData->limit->min << "-" << fieldData->limit->max << ")";
        }

        QHBoxLayout *hBoxLt = new QHBoxLayout();
        hBoxLt->setContentsMargins(5, 2, 5, 2);
        hBoxLt->setSpacing(5);

        QLabel *nameField = new QLabel(QString::fromStdString(it), frameGroupBox);
        nameField->setMinimumWidth(150);
        hBoxLt->addWidget(nameField);

        // Min field
        hBoxLt->addWidget(new QLabel("Min: ", frameGroupBox));
        QLineEdit *minTxtEdt = new QLineEdit(frameGroupBox);
        minTxtEdt->setValidator(new QIntValidator(INT_MIN, INT_MAX, this));
        minTxtEdt->setText(QString::number(fieldData->limit->min));
        minTxtEdt->setMinimumWidth(100);

        connect(minTxtEdt, &QLineEdit::textChanged,
                [sensorName, fieldData, this, minTxtEdt]() {
                    bool ok = false;
                    int value = minTxtEdt->text().toInt(&ok);
                    if (ok) {
                        fieldData->limit->min = value;
                        SensorSettingsManager::saveSensor(sensorName, fieldData);
                    }
                });
        hBoxLt->addWidget(minTxtEdt);

        // Max field
        hBoxLt->addWidget(new QLabel("Max: ", frameGroupBox));
        QLineEdit *maxTxtEdt = new QLineEdit(frameGroupBox);
        maxTxtEdt->setValidator(new QIntValidator(INT_MIN, INT_MAX, this));
        maxTxtEdt->setText(QString::number(fieldData->limit->max));
        maxTxtEdt->setMinimumWidth(100);

        connect(maxTxtEdt, &QLineEdit::textChanged,
                [sensorName, fieldData, this, maxTxtEdt]() {
                    bool ok = false;
                    int value = maxTxtEdt->text().toInt(&ok);
                    if (ok) {
                        fieldData->limit->max = value;
                        SensorSettingsManager::saveSensor(sensorName, fieldData);
                    }
                });
        hBoxLt->addWidget(maxTxtEdt);

        // Checkbox
        QCheckBox *checkBox = new QCheckBox("Детал.", frameGroupBox);
        checkBox->setChecked(fieldData->settings->useDetalaizedLimits);
        connect(checkBox, &QCheckBox::toggled, [fieldData, it, sensorName,  this](bool checked) {
            fieldData->settings->useDetalaizedLimits = checked;
            SensorSettingsManager::saveSensor(sensorName, fieldData);
        });
        hBoxLt->addWidget(checkBox);

        // Details button
        QPushButton *openLimitsDetail = new QPushButton("...", frameGroupBox);
        connect(openLimitsDetail, &QPushButton::clicked, [frameShared, fieldData, sensorName]() {
            DetailingLimitsWidget *detatlsLimits = new DetailingLimitsWidget(fieldData, sensorName);
            detatlsLimits->setAttribute(Qt::WA_DeleteOnClose);
            detatlsLimits->show();
        });
        hBoxLt->addWidget(openLimitsDetail);

        hBoxLt->addStretch();
        frameGroupBox->addLayout(hBoxLt);
    }

    frameGroupBox->setExpanded(false);
    framesVBLt->addWidget(frameGroupBox, 0, Qt::AlignTop | Qt::AlignLeft);
}
