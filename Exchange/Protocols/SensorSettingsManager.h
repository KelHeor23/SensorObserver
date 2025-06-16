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
    static bool saveAll(const QString& organization, const QString& appName,
                        const SensorHashTable& data);

    // Загрузить всю таблицу
    static bool loadAll(const QString& organization, const QString& appName,
                        SensorHashTable& outData);

    // Сохранить отдельный сенсор
    static bool saveSensor(const QString& organization, const QString& appName,
                           const QString& sensorName, std::shared_ptr<SensorData> data);

    // Загрузить отдельный сенсор
    static bool loadSensor(const QString& organization, const QString& appName,
                           const QString& sensorName, std::shared_ptr<SensorData> outData);

    // Удалить отдельный сенсор
    static bool removeSensor(const QString& organization, const QString& appName,
                             const QString& sensorName);
};
#endif // SENSORSETTINGSMANAGER_H
