#ifndef SENSORSFRAMES_H
#define SENSORSFRAMES_H

#include <unordered_map>
#include <memory>

#include "Data/Frames/Frames.h"
#include "Base.h"

class SensorsFrames
{
public:
    SensorsFrames();

    std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>>& getFrames();

    std::shared_ptr<SensorData> fastFind(const SensorName& name) const;
    void rebuildIndex();
private:

private:
    std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>> frames;
    std::unordered_map<SensorName, std::weak_ptr<SensorData>> index;
};

#endif // SENSORSFRAMES_H
