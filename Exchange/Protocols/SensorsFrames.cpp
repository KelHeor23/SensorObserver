#include "SensorsFrames.h"

#include "EngineSensors/EngineSensors.h"
#include "Exchange/Protocols/EscSensors/EscSensors.h"
#include "Exchange/Protocols/VoltageRegulators/VoltageRegulators.h"

SensorsFrames::SensorsFrames()
{
    frames[ESC] = std::make_shared<EscSensors::EscSensors>();
    frames[ENGINE] = std::make_shared<EngineSensors::EngineSensors>();
    frames[VOLTAGE_REGULATORS] = std::make_shared<VoltageRegulators::VoltageRegulators>();
}

std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol> > SensorsFrames::getFrames() const
{
    return frames;
}
