#ifndef ESCSTATUS2_H
#define ESCSTATUS2_H

#include "Exchange/Protocols/Base.h"

namespace EscSensors {
class EscStatus2 : public BaseProtocol
{
public:
    EscStatus2();
    void setData(std::string_view data) override;
};
}

#endif // ESCSTATUS2_H
