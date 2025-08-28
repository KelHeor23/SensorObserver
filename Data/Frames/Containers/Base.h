#ifndef BASE_H
#define BASE_H

#include "Sensors.h"
#include "Data/CommonTypes.h"

class BaseProtocol {

public:
    const auto& getFields() const   { return fields; }
    auto& getFields()               { return fields; }

    virtual void setData(std::string_view data, int16_t node_id) = 0;
public:
    FrameName nameFrame;
    std::vector<SensorName> orderedNames;
    std::unordered_map<SensorName, std::shared_ptr<SensorData>> fields;

    FrameName getNameFrame() const;
};

inline FrameName BaseProtocol::getNameFrame() const
{
    return nameFrame;
}

#endif // BASE_H
