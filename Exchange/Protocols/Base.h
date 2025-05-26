#ifndef BASE_H
#define BASE_H

#include <unordered_map>
#include <vector>

#include "Sensors.h"

class BaseProtocol {

public:
    QString nameFrame;
    std::vector<SensorName> orderedNames;
    std::unordered_map<SensorName, SensorData> fields;
};

#endif // BASE_H
