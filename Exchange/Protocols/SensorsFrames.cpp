#include "SensorsFrames.h"

SensorsFrames::SensorsFrames():
    engineSensors(new EngineSensors::EngineSensors),
    voltageRegulatorsSensors(new VoltageRegulators::VoltageRegulators),
    escSensors(new EscSensors::EscSensors)
{

}

EngineSensors::EngineSensors *SensorsFrames::getEngineSensors() const
{
    return engineSensors;
}
