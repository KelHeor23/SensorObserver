#include "SensorsFrames.h"

#include "EngineSensors/EngineSensors.h"
#include "Exchange/Protocols/EscSensors/EscSensors.h"
#include "Exchange/Protocols/VoltageRegulators/VoltageRegulators.h"

SensorsFrames::SensorsFrames()
{
    frames.push_back(std::make_shared<EngineSensors::EngineSensors>());
    frames.push_back(std::make_shared<VoltageRegulators::VoltageRegulators>());
    frames.push_back(std::make_shared<EscSensors::EscSensors>());
}

std::list<std::shared_ptr<BaseProtocol> > SensorsFrames::getFrames() const
{
    return frames;
}
