/**
 * \file SensorSettingsManager.h
 * \brief Сохранение/загрузка настроек сенсоров.
 * \details Работает с QSettings (INI) для набора сенсоров и для отдельных сенсоров. Путь к конфигу формируется в каталоге приложения.
 */

#ifndef SENSORSETTINGSMANAGER_H
#define SENSORSETTINGSMANAGER_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QSettings>
#include <QHash>
#include <QString>
#endif

#include "Sensors.h"
/**
 * \class SensorSettingsManager
 * \brief Сохранение и загрузка настроек сенсоров через QSettings.
 * \details Формирует путь к INI в каталоге приложения и предоставляет
 * операции сохранения/загрузки всех сенсоров и отдельных элементов.
 */

class SensorSettingsManager {
    using SensorPtr = std::shared_ptr<SensorData>;
    using SensorHashTable = std::unordered_map<QString, SensorPtr>;

public:
    /** \return Полный путь к INI-файлу (config/sensors.ini) в каталоге приложения. */

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

