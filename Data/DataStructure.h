/**
 * \file DataStructure.h
 * \brief Хранилище временных рядов телеметрии по двигателям/кадрам/сенсорам.
 * \details Для каждого двигателя хранит набор фреймов; каждый фрейм содержит набор сенсоров с историей значений (std::vector<double>).
 */

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include "Data/CommonTypes.h"
#include "Frames/Frames.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <unordered_map>
#include <vector>
#endif

/**
 * \class DataStructure
 * \brief Централизованное хранилище временных рядов телеметрии.
 * \details
 *  - Индексация по номеру двигателя (engineNum), затем по имени фрейма (FrameName),
 *    затем по имени сенсора (SensorName) с историей значений (std::vector<double>).
 *  - Предназначено для построения графиков и экспорта в CSV.
 *  - Потокобезопасность не обеспечивается: вызывать из GUI/основного потока.
 */

class DataStructure
{
    /** \typedef Data
 *  \brief История значений одного сенсора.
 */
    using Data          = std::vector<double>;
    /** \typedef SensorData
 *  \brief Набор временных рядов по сенсорам внутри одного фрейма.
 */
    using SensorData    = std::unordered_map<SensorName, Data>;         // датчик и все пришедшие данные данные
    /** \typedef FrameData
 *  \brief База всех данных для двигателя: множество фреймов и их сенсоров.
 */
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
