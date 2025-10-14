#include "DataStructure.h"
#include "qdatetime.h"

#include <stdexcept>

DataStructure::DataStructure() {
    engines.resize(8);
}

void DataStructure::addData(size_t engineNum, std::string frameName, FrameTypes type, std::shared_ptr<BaseFrame> data) {
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
        addEngineSensorsData(engineNum, frameName, data);
        break;
    case ESC_FRAME1:
        addEscStatusInfo1Data(engineNum, frameName, data);
        break;
    case ESC_FRAME2:
        addEscStatusInfo2Data(engineNum, frameName, data);
        break;
    case ESC_FRAME3:
        addEscStatusInfo3Data(engineNum, frameName, data);
        break;
    case VOLTAGE_REGULATORS:
        addVoltageRegulatorSensorsData(engineNum, frameName, data);
        break;
    case OTHER_SENSROS:
        addOtherSensorsData(engineNum, frameName, data);
        break;
    default:
        throw std::invalid_argument("Unknown frame type");
    }
}

void DataStructure::addEngineSensorsData(size_t engineNum, const std::string &frameName, std::shared_ptr<BaseFrame> data) {
    auto castedData = std::static_pointer_cast<EngineSensorsData>(data);
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.);
    addValueToFrame(engineNum, frameName, "Угол биения", castedData->runoutAngle);
    addValueToFrame(engineNum, frameName, "Амплитуда биения", castedData->runoutAmplitude);
}

void DataStructure::addVoltageRegulatorSensorsData(size_t engineNum, const std::string &frameName, std::shared_ptr<BaseFrame> data) {
    auto castedData = std::static_pointer_cast<VoltageRegulatorsData>(data);
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.);
    addValueToFrame(engineNum, frameName, "Среднее напряжение A", castedData->averageVoltageA);
    addValueToFrame(engineNum, frameName, "Среднее напряжение B", castedData->averageVoltageB);
    addValueToFrame(engineNum, frameName, "Среднее напряжение C", castedData->averageVoltageC);
}

void DataStructure::addOtherSensorsData(size_t engineNum, const std::string &frameName, std::shared_ptr<BaseFrame>  data)
{
    auto castedData = std::static_pointer_cast<OtherSensorsData>(data);
    addValueToFrame(engineNum, frameName, "Тяга", castedData->weight);
}

void DataStructure::addEscStatusInfo1Data(size_t engineNum, const std::string &frameName, std::shared_ptr<BaseFrame> data) {
    auto castedData = std::static_pointer_cast<EscSensors::EscStatusInfo1>(data);
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toSecsSinceEpoch() / 1000.);
    addValueToFrame(engineNum, frameName, "RPM мотор", castedData->speed);
    addValueToFrame(engineNum, frameName, "recv_pwm", castedData->recv_pwm);
    addValueToFrame(engineNum, frameName, "comm_pwm", castedData->comm_pwm);
}

void DataStructure::addEscStatusInfo2Data(size_t engineNum, const std::string &frameName, std::shared_ptr<BaseFrame> data) {
    auto castedData = std::static_pointer_cast<EscSensors::EscStatusInfo2>(data);
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toSecsSinceEpoch() / 1000.);
    addValueToFrame(engineNum, frameName, "Напряжение шины", castedData->voltage);
    addValueToFrame(engineNum, frameName, "Ток шины", castedData->bus_current);
    addValueToFrame(engineNum, frameName, "Ток мотора", castedData->current);
}

void DataStructure::addEscStatusInfo3Data(size_t engineNum, const std::string &frameName, std::shared_ptr<BaseFrame> data) {
    auto castedData = std::static_pointer_cast<EscSensors::EscStatusInfo3>(data);
    addValueToFrame(engineNum, frameName, "Time", QDateTime::currentDateTime().toSecsSinceEpoch() / 1000.);
    addValueToFrame(engineNum, frameName, "Температура конденсатора", castedData->cap_temp);
    addValueToFrame(engineNum, frameName, "Температура MCU", castedData->mcu_temp);
    addValueToFrame(engineNum, frameName, "Температура мотора", castedData->motor_temp);
    addValueToFrame(engineNum, frameName, "Ошибка", castedData->Error);
}

template<typename T>
void DataStructure::addValueToFrame(size_t engineNum, const std::string &frameName, const std::string &key, T value){
    auto& engineData = engines.at(engineNum);
    auto& frameData = engineData[frameName];
    frameData[key].push_back(value);
}
