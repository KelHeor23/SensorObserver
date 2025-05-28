#ifndef SENSORSFRAMES_H
#define SENSORSFRAMES_H

#include <list>
#include <memory>

#include "Base.h"

class SensorsFrames
{
public:
    SensorsFrames();

    std::list<std::shared_ptr<BaseProtocol> > getFrames() const;

private:
    std::list<std::shared_ptr<BaseProtocol>> frames;
};

#endif // SENSORSFRAMES_H
