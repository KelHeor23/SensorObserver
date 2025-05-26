#include "Frames.h"

Frames::Frames():
    engineSensors(new EngineSensors::EngineSensors),
    voltageRegulatorsSensors(new VoltageRegulators::VoltageRegulators),
    escSensors(new EscSensors::EscSensors)
{

}
