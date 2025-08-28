#ifndef SENSORSETTINGSMANAGER_H
#define SENSORSETTINGSMANAGER_H

#include <QSettings>
#include <QHash>
#include <QString>

#include "Sensors.h"

class SensorSettingsManager {
    using SensorPtr = std::shared_ptr<SensorData>;
    using SensorHashTable = std::unordered_map<QString, SensorPtr>;

public:

    static QString getConfigPath();

    // Сохранить всю таблицу
    static bool saveAll(const SensorHashTable& data);

    // Загрузить всю таблицу
    static bool loadAll(SensorHashTable& outData);

    // Сохранить отдельный сенсор
    static bool saveSensor(const QString& sensorName, SensorPtr data);

    // Загрузить отдельный сенсор
    static bool loadSensor(const QString& sensorName, SensorPtr outData);

    // Удалить отдельный сенсор
    static bool removeSensor(const QString& sensorName);


    const QString organization = "Breez";
    const QString appName = "SensorApp";
};
#endif // SENSORSETTINGSMANAGER_H
