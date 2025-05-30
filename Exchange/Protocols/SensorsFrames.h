#ifndef SENSORSFRAMES_H
#define SENSORSFRAMES_H

#include <unordered_map>
#include <memory>

#include "Base.h"

enum FrameTypes{
    ESC,
    ENGINE,
    VOLTAGE_REGULATORS
};

class SensorsFrames
{
public:
    SensorsFrames();

    std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>>& getFrames();

private:
    std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>> frames;
};

#endif // SENSORSFRAMES_H
