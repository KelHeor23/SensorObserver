/**
 * \file SensorsFrames.cpp
 * \brief Реализация реестра фреймов сенсоров.
 * \details Создаёт и регистрирует контейнеры кадрам (ESC, Engine, VoltageRegulators и т.д.), поддерживает переиндексацию полей.
 */

#include "SensorsFrames.h"
#include "EngineSensors/EngineSensors.h"
#include "Data/Frames/Containers/EscSensors/EscStatus1.h"
#include "Data/Frames/Containers/EscSensors/EscStatus2.h"
#include "Data/Frames/Containers/EscSensors/EscStatus3.h"
#include "Data/Frames/Containers/VoltageRegulators/VoltageRegulators.h"
#include "Data/Frames/Containers/OtherSensors/OtherSensors.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "qdebug.h"
#endif
/**
 * \brief Регистрирует доступные фреймы в реестре.
 * \details Инициализирует контейнеры для ESC (status1/2/3), Engine, VoltageRegulators, OtherSensors.
 */

SensorsFrames::SensorsFrames()
{
    frames[ESC_FRAME1] = std::make_shared<EscSensors::EscStatus1>();
    frames[ESC_FRAME2] = std::make_shared<EscSensors::EscStatus2>();
    frames[ESC_FRAME3] = std::make_shared<EscSensors::EscStatus3>();
    frames[ENGINE] = std::make_shared<EngineSensors::EngineSensors>();
    frames[VOLTAGE_REGULATORS] = std::make_shared<VoltageRegulators::VoltageRegulators>();
    frames[OTHER_SENSROS] = std::make_shared<OtherSensors::OtherSensors>();

    rebuildIndex();
}

std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>>& SensorsFrames::getFrames()
{
    return frames;
}

std::shared_ptr<SensorData> SensorsFrames::fastFind(const SensorName &name) const {
    auto it = index.find(name);
    if (it == index.end()) {
        qDebug() << "Датчик не найден:" << &name; // Логировать отсутствующие имена
        return nullptr;
    }
    return it->second.lock();
}
/**
 * \brief Перестраивает индекс сенсоров.
 * \details Проходит по всем фреймам и добавляет их поля в словарь быстрого доступа
 * по имени сенсора. Используется после изменения набора фреймов или их полей.
 */

void SensorsFrames::rebuildIndex()
{
    index.clear();
    for (const auto& frame : frames) {
        for (const auto& field : frame.second->fields) {
            index[field.first] = field.second;
        }
    }
}

