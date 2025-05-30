#ifndef BASE_H
#define BASE_H

#include <unordered_map>
#include <vector>

#include "Sensors.h"

class BaseProtocol {

public:
    std::unordered_map<SensorName, SensorData>& getFields() {
        return fields;
    }

    virtual void setData(std::string_view data) = 0;

public:
    QString nameFrame;
    std::vector<SensorName> orderedNames;
    std::unordered_map<SensorName, SensorData> fields;

};

#endif // BASE_H
