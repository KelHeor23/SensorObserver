#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include "Data/CommonTypes.h"
#include "Frames/Frames.h"
#include <unordered_map>
#include <vector>

class DataStructure
{
    using Data          = std::vector<double>;
    using SensorData    = std::unordered_map<SensorName, Data>;         // датчик и все пришедшие данные данные
    using FrameData     = std::unordered_map<FrameName, SensorData>;    // база всех данных датчиков
public:
    static DataStructure& Instance(){
        static DataStructure obj;
        return obj;
    };

    void addData(size_t engineNum, std::string frameName, FrameTypes type, std::shared_ptr<BaseFrame> data);

private:
    DataStructure();

    template<typename T>
    void addValueToFrame(size_t engineNum, const std::string &frameName, const std::string& key, T value);

    void addEngineSensorsData(size_t engineNum, const std::string &type, std::shared_ptr<BaseFrame> data);
    void addVoltageRegulatorSensorsData(size_t engineNum, const std::string &type, std::shared_ptr<BaseFrame> data);
    void addOtherSensorsData(size_t engineNum,  const std::string &type, std::shared_ptr<BaseFrame> data);
    void addEscStatusInfo1Data(size_t engineNum, const std::string &type, std::shared_ptr<BaseFrame> data);
    void addEscStatusInfo2Data(size_t engineNum, const std::string &type, std::shared_ptr<BaseFrame> data);
    void addEscStatusInfo3Data(size_t engineNum, const std::string &type, std::shared_ptr<BaseFrame> data);

public:
    std::vector<FrameData> engines; // вектор объединяющий
};

#endif // DATASTRUCTURE_H
