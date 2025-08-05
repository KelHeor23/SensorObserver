#include "DataStructure.h"
#include "qdebug.h"

void DataStructure::addData(FrameTypes type, BaseFrame data)
{
    if (type == NONE)
    {
        qWarning() << "DataStructure::addData. FrameTypes alert!";
        return;
    }



}
