#include "SensorsFrames.h"

#include "EngineSensors/EngineSensors.h"
#include "Data/Frames/Containers/EscSensors/EscStatus1.h"
#include "Data/Frames/Containers/EscSensors/EscStatus2.h"
#include "Data/Frames/Containers/EscSensors/EscStatus3.h"
#include "Data/Frames/Containers/VoltageRegulators/VoltageRegulators.h"
#include "Data/Frames/Containers/OtherSensors/OtherSensors.h"
#include "qdebug.h"

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

void SensorsFrames::rebuildIndex()
{
    index.clear();
    for (const auto& frame : frames) {
        for (const auto& field : frame.second->fields) {
            index[field.first] = field.second;
        }
    }
}
