#ifndef SENSORSETTINGSMANAGER_H
#define SENSORSETTINGSMANAGER_H

#include <QSettings>
#include <QHash>
#include <QString>

#include "Sensors.h"

class SensorSettingsManager {
public:
    using SensorHashTable = std::unordered_map<QString, SensorData>;

    static QString getConfigPath();

    // Сохранить всю таблицу
    static bool saveAll(const SensorHashTable& data);

    // Загрузить всю таблицу
    static bool loadAll(SensorHashTable& outData);

    // Сохранить отдельный сенсор
    static bool saveSensor(const QString& sensorName, std::shared_ptr<SensorData> data);

    // Загрузить отдельный сенсор
    static bool loadSensor(const QString& sensorName, std::shared_ptr<SensorData> outData);

    // Удалить отдельный сенсор
    static bool removeSensor(const QString& sensorName);


    const QString organization = "Breez";
    const QString appName = "SensorApp";
};
#endif // SENSORSETTINGSMANAGER_H
