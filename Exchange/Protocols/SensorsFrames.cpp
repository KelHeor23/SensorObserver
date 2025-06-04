#include "SensorsFrames.h"

#include "EngineSensors/EngineSensors.h"
#include "Exchange/Protocols/EscSensors/EscStatus1.h"
#include "Exchange/Protocols/EscSensors/EscStatus2.h"
#include "Exchange/Protocols/EscSensors/EscStatus3.h"
#include "Exchange/Protocols/VoltageRegulators/VoltageRegulators.h"

SensorsFrames::SensorsFrames()
{
    frames[ESC_FRAME1] = std::make_shared<EscSensors::EscStatus1>();
    frames[ESC_FRAME2] = std::make_shared<EscSensors::EscStatus2>();
    frames[ESC_FRAME3] = std::make_shared<EscSensors::EscStatus3>();
    frames[ENGINE] = std::make_shared<EngineSensors::EngineSensors>();
    frames[VOLTAGE_REGULATORS] = std::make_shared<VoltageRegulators::VoltageRegulators>();
}

std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>>& SensorsFrames::getFrames()
{
    return frames;
}
