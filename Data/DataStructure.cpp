/**
 * \file DataStructure.cpp
 * \brief Реализация хранилища телеметрии и маршрутизации поступающих кадров.
 * \details Проверяет входные аргументы, кастует данные по типу фрейма и добавляет значения в соответствующие ряды.
 */

#include "DataStructure.h"
#include "qdatetime.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <stdexcept>
#endif
/**
 * \brief Инициализирует хранилище на 8 двигателей по умолчанию.
 * \note Размер можно изменить в будущем, если число двигателей иное.
 */

DataStructure::DataStructure() {
    engines.resize(8);
}
/**
 * \brief Добавляет значения из расшифрованного кадра в хранилище.
 * \param[in] engineNum Номер двигателя (индекс в векторе).
 * \param[in] frameName Имя фрейма (логическая группа параметров).
 * \param[in] type Тип кадра (маршрутизация на конкретную структуру).
 * \param[in] data Указатель на базовую структуру кадра.
 * \throws std::out_of_range Если engineNum вне диапазона.
 * \throws std::invalid_argument Если data == nullptr.
 * \details Выполняет безопасный static_pointer_cast к нужной структуре
 *           и кладёт поля в соответствующие временные ряды через addValueToFrame().
 */

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
    addValueToFrame(engineNum, frameName, "Реакт. мом. двиг 1", castedData->reactiveTorquEngine1);
    addValueToFrame(engineNum, frameName, "Реакт. мом. двиг 2", castedData->reactiveTorquEngine2);
    addValueToFrame(engineNum, frameName, "Тяга 1", castedData->thrustEngine1);
    addValueToFrame(engineNum, frameName, "Тяга 2", castedData->thrustEngine2);
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
/**
 * \brief Утилита для добавления значения в конкретную ячейку хранилища.
 * \tparam T Числовой тип значения (приводится к double при хранении).
 * \param[in] engineNum Двигатель.
 * \param[in] frameName Имя фрейма.
 * \param[in] key Имя сенсора.
 * \param[in] value Значение (в целевых единицах).
 * \post Создаёт недостающие уровни и дописывает значение в конец ряда.
 */

template<typename T>
void DataStructure::addValueToFrame(size_t engineNum, const std::string &frameName, const std::string &key, T value){
    auto& engineData = engines.at(engineNum);
    auto& frameData = engineData[frameName];
    frameData[key].push_back(value);
}
