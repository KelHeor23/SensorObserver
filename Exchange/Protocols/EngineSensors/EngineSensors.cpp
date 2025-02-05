#include "EngineSensors.h"

EngineSensors::EngineSensors() {
    sensorsData.push_back(NodeSensor{"Обороты", 0, 0});
    sensorsData.push_back(NodeSensor{"Температура", 0, 0});
    sensorsData.push_back(NodeSensor{"Угол биения", 0, 0});
    sensorsData.push_back(NodeSensor{"Амплитуда биения", 0, 0});
}

void EngineSensors::EngineSensorsData::parseEngineSensorsData(const uint8_t *data)
{
    size_t offset = 0;
    memcpy(&this->canID, data + offset, offset);
    offset += sizeof(this->canID);
    memcpy(&this->speed, data + offset, sizeof(this->speed));
    offset += sizeof(this->speed);
    memcpy(&this->temperature, data + offset, sizeof(this->temperature));
    offset += sizeof(this->temperature);
    memcpy(&this->runoutAngle, data + offset, sizeof(this->runoutAngle));
    offset += sizeof(this->runoutAngle);
    memcpy(&this->runoutAmplitude, data + offset, sizeof(this->runoutAmplitude));
}
