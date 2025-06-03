#ifndef ESCSTATUS3_H
#define ESCSTATUS3_H

#include "Exchange/Protocols/Base.h"

namespace EscSensors {
class EscStatus3 : public BaseProtocol
{
public:
    EscStatus3();
    void setData(std::string_view data) override;
};
}

#endif // ESCSTATUS3_H
