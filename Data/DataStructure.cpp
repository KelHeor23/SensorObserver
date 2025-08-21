#include "DataStructure.h"
#include "qdatetime.h"

#include <stdexcept>

DataStructure::DataStructure() {
    engines.resize(8);
}

void DataStructure::addData(size_t engineNum, QString frameName, FrameTypes type, BaseFrame *data) {
    if (engineNum >= engines.size()) {
        throw std::out_of_range("Incorrect engine index");
    }
    if (!data) {
        throw std::invalid_argument("Data pointer is null");
    }

    switch (type) {
    case NONE:
        throw std::invalid_argument("Invalid frame type: NONE");
    case ENGINE:
        addEngineSensorsData(engineNum, frameName, static_cast<EngineSensorsData*>(data));
        break;
    case ESC_FRAME1:
        addEscStatusInfo1Data(engineNum, frameName, static_cast<EscSensors::EscStatusInfo1*>(data));
        break;
    case ESC_FRAME2:
        addEscStatusInfo2Data(engineNum, frameName, static_cast<EscSensors::EscStatusInfo2*>(data));
        break;
    case ESC_FRAME3:
        addEscStatusInfo3Data(engineNum, frameName, static_cast<EscSensors::EscStatusInfo3*>(data));
        break;
    case VOLTAGE_REGULATORS:
        addVoltageRegulatorSensorsData(engineNum, frameName, static_cast<VoltageRegulatorsData*>(data));
        break;
    default:
        throw std::invalid_argument("Unknown frame type");
    }
}

void DataStructure::addEngineSensorsData(size_t engineNum, const QString &frameName, EngineSensorsData* data) {
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.);
    addValueToFrame(engineNum, frameName, "Угол биения", data->runoutAngle);
    addValueToFrame(engineNum, frameName, "Амплитуда биения", data->runoutAmplitude);
}

void DataStructure::addVoltageRegulatorSensorsData(size_t engineNum, const QString &frameName, VoltageRegulatorsData *data) {
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toMSecsSinceEpoch());
    addValueToFrame(engineNum, frameName, "Среднее напряжение A", data->averageVoltageA);
    addValueToFrame(engineNum, frameName, "Среднее напряжение B", data->averageVoltageB);
    addValueToFrame(engineNum, frameName, "Среднее напряжение C", data->averageVoltageC);
}

void DataStructure::addEscStatusInfo1Data(size_t engineNum, const QString &frameName, EscSensors::EscStatusInfo1 *data) {
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toSecsSinceEpoch());
    addValueToFrame(engineNum, frameName, "RPM мотор", data->speed);
    addValueToFrame(engineNum, frameName, "recv_pwm", data->recv_pwm);
    addValueToFrame(engineNum, frameName, "comm_pwm", data->comm_pwm);
}

void DataStructure::addEscStatusInfo2Data(size_t engineNum, const QString &frameName, EscSensors::EscStatusInfo2* data) {
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toSecsSinceEpoch());
    addValueToFrame(engineNum, frameName, "Напряжение шины", data->voltage);
    addValueToFrame(engineNum, frameName, "Ток шины", data->bus_current);
    addValueToFrame(engineNum, frameName, "Ток мотора", data->current);
}

void DataStructure::addEscStatusInfo3Data(size_t engineNum, const QString &frameName, EscSensors::EscStatusInfo3* data) {
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toSecsSinceEpoch());
    addValueToFrame(engineNum, frameName, "Температура конденсатора", data->cap_temp);
    addValueToFrame(engineNum, frameName, "Температура MCU", data->mcu_temp);
    addValueToFrame(engineNum, frameName, "Температура мотора", data->motor_temp);
    addValueToFrame(engineNum, frameName, "Ошибка", data->Error);
}

template<typename T>
void DataStructure::addValueToFrame(size_t engineNum, const QString &frameName, const QString &key, T value){
    auto& engineData = engines.at(engineNum);
    auto& frameData = engineData[frameName];
    frameData[key].push_back(value);
}
