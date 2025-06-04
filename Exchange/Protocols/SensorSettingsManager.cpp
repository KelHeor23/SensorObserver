#include "SensorSettingsManager.h"

#include <QCoreApplication>
#include <QDir>

QString SensorSettingsManager::getConfigPath()
{
    QString appDir = QCoreApplication::applicationDirPath();
    QDir dir(appDir);
    if (!dir.exists("config")) {
        dir.mkdir("config");
    }
    return appDir + "/config/sensors.ini";
}

bool SensorSettingsManager::saveAll(const QString &organization, const QString &appName, const SensorHashTable &data) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors");
    settings.remove(""); // Очищаем предыдущие данные

    for (auto it = data.begin(); it != data.end(); ++it) {
        settings.beginGroup(it->first);
        settings.setValue("value", it->second.val);
        settings.setValue("min_limit", it->second.limit->min);
        settings.setValue("max_limit", it->second.limit->max);
        settings.endGroup();
    }

    settings.endGroup();
    return settings.status() == QSettings::NoError;
}

bool SensorSettingsManager::loadAll(const QString &organization, const QString &appName, SensorHashTable &outData) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    outData.clear();

    settings.beginGroup("Sensors");
    QStringList sensorKeys = settings.childGroups();

    for (const QString& key : sensorKeys) {
        settings.beginGroup(key);

        SensorData sensor;
        sensor.val = settings.value("value", 0).toInt();
        sensor.limit->min = settings.value("min_limit", 0).toInt();
        sensor.limit->max = settings.value("max_limit", 0).toInt();

        outData[key] = sensor;
        settings.endGroup();
    }

    settings.endGroup();
    return settings.status() == QSettings::NoError;
}

bool SensorSettingsManager::saveSensor(const QString &organization, const QString &appName, const QString &sensorName, const SensorData &data) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors/" + sensorName);
    settings.setValue("value", data.val);
    settings.setValue("min_limit", data.limit->min);
    settings.setValue("max_limit", data.limit->max);
    settings.endGroup();

    return settings.status() == QSettings::NoError;
}

bool SensorSettingsManager::loadSensor(const QString &organization, const QString &appName, const QString &sensorName, SensorData &outData) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors/" + sensorName);

    if (!settings.contains("value")) {
        settings.endGroup();
        return false;
    }

    outData.val = settings.value("value", 0).toInt();
    outData.limit->min = settings.value("min_limit", 0).toInt();
    outData.limit->max = settings.value("max_limit", 0).toInt();

    settings.endGroup();
    return settings.status() == QSettings::NoError;
}

bool SensorSettingsManager::removeSensor(const QString &organization, const QString &appName, const QString &sensorName) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors");
    settings.remove(sensorName);
    settings.endGroup();

    return settings.status() == QSettings::NoError;
}
