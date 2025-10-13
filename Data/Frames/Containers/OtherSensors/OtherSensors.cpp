#include "OtherSensors.h"

OtherSensors::OtherSensors() {
    nameFrame = "Остальные датчики";
    orderedNames = sensorNames;

    for (auto &it : orderedNames){
        fields[it] = std::make_shared<SensorData>();
        fields[it]->val = 0;
    }
}
