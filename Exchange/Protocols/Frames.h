#ifndef FRAMES_H
#define FRAMES_H

#include "EngineSensors/EngineSensors.h"
#include "Exchange/Protocols/EscSensors/EscSensors.h"
#include "Exchange/Protocols/VoltageRegulators/VoltageRegulators.h"

class Frames
{
public:
    Frames();

private:
    EngineSensors::EngineSensors *engineSensors;
    VoltageRegulators::VoltageRegulators *voltageRegulatorsSensors;
    EscSensors::EscSensors *escSensors;
};

#endif // FRAMES_H
