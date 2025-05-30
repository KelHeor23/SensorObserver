#ifndef ESCSENSORS_H
#define ESCSENSORS_H

#include <string_view>
#include <unordered_map>
#include <vector>

#include "Exchange/Protocols/Sensors.h"
#include "Exchange/Protocols/Base.h"

namespace EscSensors {

class EscSensors : public BaseProtocol
{

public:
    EscSensors();

    void setData(std::string_view data) override;
    void setDataESC(uint16_t frame_id, std::string_view data);
};

}


#endif // ESCSENSORS_H
