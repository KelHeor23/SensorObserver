#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <QVector>

#include "Frames/Frames.h"

class DataStructure
{
    using SensorName    = QString;
    using FrameName     = QString;
    using Data          = QVector<double>;
    using SensorData    = std::unordered_map<SensorName, Data>;         // датчик и все пришедшие данные данные
    using FrameData     = std::unordered_map<FrameName, SensorData>;    // база всех данных датчиков



public:
    static DataStructure& Instance(){
        static DataStructure obj;
        return obj;
    };

    void addData(size_t engineNum, QString frameName, FrameTypes type, BaseFrame *data);

private:
    DataStructure();

    template<typename T>
    void addValueToFrame(size_t engineNum, const QString &frameName, const QString& key, T value);

    void addEngineSensorsData(size_t engineNum, const QString &type, EngineSensorsData *data);
    void addVoltageRegulatorSensorsData(size_t engineNum, const QString &type, VoltageRegulatorsData *data);
    void addEscStatusInfo1Data(size_t engineNum, const QString &type, EscSensors::EscStatusInfo1 *data);
    void addEscStatusInfo2Data(size_t engineNum, const QString &type, EscSensors::EscStatusInfo2 *data);
    void addEscStatusInfo3Data(size_t engineNum, const QString &type, EscSensors::EscStatusInfo3 *data);

public:
    std::vector<FrameData> engines; // вектор объединяющий
};

#endif // DATASTRUCTURE_H
