#ifndef SENSORSFRAMES_H
#define SENSORSFRAMES_H

#include "EngineSensors/EngineSensors.h"
#include "Exchange/Protocols/EscSensors/EscSensors.h"
#include "Exchange/Protocols/VoltageRegulators/VoltageRegulators.h"

class SensorsFrames
{
public:
    SensorsFrames();

    EngineSensors::EngineSensors *getEngineSensors() const;

private:
    EngineSensors::EngineSensors *engineSensors;
    VoltageRegulators::VoltageRegulators *voltageRegulatorsSensors;
    EscSensors::EscSensors *escSensors;
};

#endif // SENSORSFRAMES_H
