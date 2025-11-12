/**
 * \file SensorsFrames.h
 * \brief Реестр и индексы доступных фреймов сенсоров.
 * \details Хранит набор объектов протоколов (BaseProtocol) для разных типов кадров и индексирует их поля по именам сенсоров для быстрого доступа.
 */

#ifndef SENSORSFRAMES_H
#define SENSORSFRAMES_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <unordered_map>
#include <memory>
#endif
#include "Data/Frames/Frames.h"
#include "Base.h"
/**
 * \class SensorsFrames
 * \brief Реестр реализованных фреймов и индекс по именам сенсоров.
 * \details Хранит объекты реализаций BaseProtocol для разных FrameTypes
 * и поддерживает индексирование поля по имени сенсора для быстрого доступа из UI.
 */

class SensorsFrames
{
public:
    SensorsFrames();

    std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>>& getFrames();

    std::shared_ptr<SensorData> fastFind(const SensorName& name) const;
    void rebuildIndex();
private:

private:
    std::unordered_map<FrameTypes, std::shared_ptr<BaseProtocol>> frames;
    std::unordered_map<SensorName, std::weak_ptr<SensorData>> index;
};

#endif // SENSORSFRAMES_H
