#include "DataStructure.h"
#include "qdebug.h"

DataStructure::DataStructure()
{
    engines.resize(8);
}

void DataStructure::addData(size_t engineNum, FrameTypes type, BaseFrame *data)
{
    if (engineNum > engines.size())
    {
        throw "Incorrect filling of the engine database";
        return;
    }

    switch(type){
    case NONE:
        throw "Incorrect frame type of the engine database";
        return;
    case ENGINE:
        addEngineSensorsData(engineNum, static_cast<EngineSensorsData*>(data));
        break;
    case ESC_FRAME1:
        break;
    case ESC_FRAME2:
        break;
    case ESC_FRAME3:
        break;
    case VOLTAGE_REGULATORS:
        break;
    };
}

void DataStructure::addEngineSensorsData(size_t engineNum, EngineSensorsData *data)
{
    auto &frameData = engines[engineNum];
}
