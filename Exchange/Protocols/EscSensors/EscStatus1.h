#ifndef ESCSTATUS1_H
#define ESCSTATUS1_H

#include "Exchange/Protocols/Base.h"

namespace EscSensors {
class EscStatus1 : public BaseProtocol
{
public:
    EscStatus1();
    void setData(std::string_view data) override;
};
}


#endif // ESCSTATUS1_H
