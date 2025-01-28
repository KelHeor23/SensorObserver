#include "EngineSensors.h"

EngineSensors::EngineSensors() {
    sensorsData.push_back(NodeSensor{"Вибрация", 0, 0});
    sensorsData.push_back(NodeSensor{"Температура", 0, 0});
    sensorsData.push_back(NodeSensor{"Что-то еще", 0, 0});
}
