#include "DataStructure.h"

#include <stdexcept>

DataStructure::DataStructure() {
    engines.resize(8);
}

void DataStructure::addData(size_t engineNum, FrameTypes type, BaseFrame *data) {
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
        addEngineSensorsData(engineNum, static_cast<EngineSensorsData*>(data));
        break;
    case ESC_FRAME1:
        addEscStatusInfo1Data(engineNum, static_cast<EscSensors::EscStatusInfo1*>(data));
        break;
    case ESC_FRAME2:
        addEscStatusInfo2Data(engineNum, static_cast<EscSensors::EscStatusInfo2*>(data));
        break;
    case ESC_FRAME3:
        addEscStatusInfo3Data(engineNum, static_cast<EscSensors::EscStatusInfo3*>(data));
        break;
    case VOLTAGE_REGULATORS:
        addVoltageRegulatorSensorsData(engineNum, static_cast<VoltageRegulatorsData*>(data));
        break;
    default:
        throw std::invalid_argument("Unknown frame type");
    }
}

void DataStructure::addEngineSensorsData(size_t engineNum, EngineSensorsData* data) {
    addValueToFrame(engineNum, FrameTypes::ENGINE, "Угол биения", data->runoutAngle);
    addValueToFrame(engineNum, FrameTypes::ENGINE, "Амплитуда биения", data->runoutAmplitude);
}

void DataStructure::addVoltageRegulatorSensorsData(size_t engineNum, VoltageRegulatorsData *data) {
    addValueToFrame(engineNum, FrameTypes::VOLTAGE_REGULATORS, "Среднее напряжение A", data->averageVoltageA);
    addValueToFrame(engineNum, FrameTypes::VOLTAGE_REGULATORS, "Среднее напряжение B", data->averageVoltageB);
    addValueToFrame(engineNum, FrameTypes::VOLTAGE_REGULATORS, "Среднее напряжение C", data->averageVoltageC);
}

void DataStructure::addEscStatusInfo1Data(size_t engineNum, EscSensors::EscStatusInfo1 *data) {
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME1, "RPM мотор", data->speed);
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME1, "recv_pwm", data->recv_pwm);
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME1, "comm_pwm", data->comm_pwm);
}

void DataStructure::addEscStatusInfo2Data(size_t engineNum, EscSensors::EscStatusInfo2* data) {
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME2, "Напряжение шины", data->voltage);
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME2, "Ток шины", data->bus_current);
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME2, "Ток мотора", data->current);
}

void DataStructure::addEscStatusInfo3Data(size_t engineNum, EscSensors::EscStatusInfo3* data) {
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME3, "Температура конденсатора", data->cap_temp);
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME3, "Температура MCU", data->mcu_temp);
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME3, "Температура мотора", data->motor_temp);
    addValueToFrame(engineNum, FrameTypes::ESC_FRAME3, "Ошибка", data->Error);
}

template<typename T>
void DataStructure::addValueToFrame(size_t engineNum, FrameTypes type, const std::string &key, T value){
    auto& engineData = engines.at(engineNum);
    auto& frameData = engineData[type];
    frameData[key].emplace_back(value);
}
