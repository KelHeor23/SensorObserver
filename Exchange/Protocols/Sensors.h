#ifndef SENSORS_H
#define SENSORS_H

#include <QString>

class Sensors {
public:
    Sensors()
    {

    }

    struct NodeSensor {
        QString name;
        int min = 0;
        int max = 0;
    };
};
#endif // SENSORS_H
