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
    auto& engineData = engines[engineNum];
    auto& frameData = engineData[ENGINE];

    frameData["Угол биения"].push_back(static_cast<int64_t>(data->runoutAngle));
    frameData["Амплитуда биения"].push_back(static_cast<int64_t>(data->runoutAmplitude));
}

void DataStructure::addVoltageRegulatorSensorsData(size_t engineNum, VoltageRegulatorsData *data) {
    auto &engineData    = engines[engineNum];
    auto &frameData     = engineData[VOLTAGE_REGULATORS];

    frameData["Среднее напряжение A"].push_back(static_cast<int>(data->averageVoltageA));
    frameData["Среднее напряжение B"].push_back(static_cast<int>(data->averageVoltageB));
    frameData["Среднее напряжение C"].push_back(static_cast<int>(data->averageVoltageC));
}

void DataStructure::addEscStatusInfo1Data(size_t engineNum, EscSensors::EscStatusInfo1 *data) {
    auto &engineData    = engines[engineNum];
    auto &frameData     = engineData[ESC_FRAME1];

    frameData["RPM motor speed"].push_back(static_cast<int>(data->speed));
    frameData["recv_pwm"].push_back(static_cast<int>(data->recv_pwm));
    frameData["comm_pwm"].push_back(static_cast<int>(data->comm_pwm));
}

void DataStructure::addEscStatusInfo2Data(size_t engineNum, EscSensors::EscStatusInfo2* data) {
    auto& engineData = engines[engineNum];
    auto& frameData = engineData[ESC_FRAME2];  // Исправлено на ESC_FRAME2

    frameData["Bus voltage"].push_back(static_cast<int64_t>(data->voltage));
    frameData["Bus current"].push_back(static_cast<int64_t>(data->bus_current));
    frameData["Motor line current"].push_back(static_cast<int64_t>(data->current));
}

void DataStructure::addEscStatusInfo3Data(size_t engineNum, EscSensors::EscStatusInfo3* data) {
    auto& engineData = engines[engineNum];
    auto& frameData = engineData[ESC_FRAME3];  // Исправлено на ESC_FRAME3

    frameData["cap_temp"].push_back(static_cast<int64_t>(data->cap_temp));
    frameData["mcu_temp"].push_back(static_cast<int64_t>(data->mcu_temp));
    frameData["motor_temp"].push_back(static_cast<int64_t>(data->motor_temp));
    frameData["Error"].push_back(static_cast<int64_t>(data->Error));
}
