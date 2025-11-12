/**
 * \file SensorSettingsManager.cpp
 * \brief Реализация менеджера настроек сенсоров (QSettings).
 * \details Операции save/load/remove для группы и заданного сенсора, а также вспомогательная функция получения пути к INI.
 */

#include "SensorSettingsManager.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QCoreApplication>
#include <QDir>
#endif

/**
 * \brief Возвращает путь к файлу настроек сенсоров.
 * \details Создаёт подкаталог \c config при необходимости и возвращает путь
 * вида <каталог_приложения>/config/sensors.ini.
 */

QString SensorSettingsManager::getConfigPath()
{
    QString appDir = QCoreApplication::applicationDirPath();
    QDir dir(appDir);
    if (!dir.exists("config")) {
        dir.mkdir("config");
    }
    return appDir + "/config/sensors.ini";
}
/** \brief Сохраняет все сенсоры в INI (группа "Sensors"). */

bool SensorSettingsManager::saveAll(const SensorHashTable &data) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors");
    settings.remove(""); // Очищаем предыдущие данные

    for (auto it = data.begin(); it != data.end(); ++it) {
        settings.beginGroup(it->first);
        settings.setValue("value", it->second->val.load());
        settings.setValue("min_limit", it->second->limit->min);
        settings.setValue("max_limit", it->second->limit->max);
        settings.setValue("useDetalaizedLimits", it->second->settings->useDetalaizedLimits);

        settings.setValue("DetalaizedLimitsCount", static_cast<int>(it->second->detalaizedLimits->size()));

        // Сохраняем каждый лимит
        for (int i = 0; i < it->second->detalaizedLimits->size(); ++i) {
            settings.beginGroup("Limit_" + QString::number(i));

            const auto& item = it->second->detalaizedLimits->at(i);
            settings.setValue("min", item.limit.min);
            settings.setValue("max", item.limit.max);
            settings.setValue("color", item.color.name(QColor::HexArgb)); // Сохраняем с альфа-каналом

            settings.endGroup();
        }

        settings.endGroup();
    }

    settings.endGroup();
    return settings.status() == QSettings::NoError;
}
/** \brief Загружает все сенсоры из INI (группа "Sensors"). */

bool SensorSettingsManager::loadAll(SensorHashTable &outData) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    outData.clear();

    settings.beginGroup("Sensors");
    QStringList sensorKeys = settings.childGroups();

    for (const QString& key : sensorKeys) {
        settings.beginGroup(key);

        SensorPtr sensor = std::make_shared<SensorData>();
        sensor->val = settings.value("value", 0).toInt();
        sensor->limit->min = settings.value("min_limit", 0).toInt();
        sensor->limit->max = settings.value("max_limit", 0).toInt();
        sensor->settings->useDetalaizedLimits = settings.value("useDetalaizedLimits", 0).toBool();

        const int count = settings.value("DetalaizedLimitsCount", 0).toInt();
        sensor->detalaizedLimits->reserve(count);

        // Загружаем каждый лимит
        for (int i = 0; i < count; ++i) {
            settings.beginGroup("Limit_" + QString::number(i));

            SensorLimitsColored item;
            item.limit.min = settings.value("min", 0).toInt();
            item.limit.max = settings.value("max", 0).toInt();

            // Восстанавливаем цвет из HEX-строки
            item.color = QColor(settings.value("color").toString());
            if (!item.color.isValid()) {
                item.color = Qt::transparent; // Фолбек на случай ошибки
            }

            sensor->detalaizedLimits->push_back(std::move(item));
            settings.endGroup();
        }

        outData[key] = sensor;
        settings.endGroup();
    }

    settings.endGroup();
    return settings.status() == QSettings::NoError;
}
/** \brief Сохраняет один сенсор под своим ключом в группе "Sensors". */

bool SensorSettingsManager::saveSensor(const QString &sensorName, SensorPtr data) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors/" + sensorName);
    settings.setValue("value", data->val.load());
    settings.setValue("min_limit", data->limit->min);
    settings.setValue("max_limit", data->limit->max);
    settings.setValue("useDetalaizedLimits", data->settings->useDetalaizedLimits);

    settings.setValue("DetalaizedLimitsCount", static_cast<int>(data->detalaizedLimits->size()));

    // Сохраняем каждый лимит
    for (int i = 0; i < data->detalaizedLimits->size(); ++i) {
        settings.beginGroup("Limit_" + QString::number(i));

        const auto& item = data->detalaizedLimits->at(i);
        settings.setValue("min", item.limit.min);
        settings.setValue("max", item.limit.max);
        settings.setValue("color", item.color.name(QColor::HexArgb)); // Сохраняем с альфа-каналом

        settings.endGroup();
    }

    settings.endGroup();

    return settings.status() == QSettings::NoError;
}
/** \brief Загружает один сенсор по имени из группы "Sensors". */

bool SensorSettingsManager::loadSensor(const QString &sensorName, std::shared_ptr<SensorData> outData) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors/" + sensorName);

    if (!settings.contains("value")) {
        settings.endGroup();
        return false;
    }

    outData->val = settings.value("value", 0).toInt();
    outData->limit->min = settings.value("min_limit", 0).toInt();
    outData->limit->max = settings.value("max_limit", 0).toInt();
    outData->settings->useDetalaizedLimits = settings.value("useDetalaizedLimits", 0).toBool();

    const int count = settings.value("DetalaizedLimitsCount", 0).toInt();
    outData->detalaizedLimits->reserve(count);

    // Загружаем каждый лимит
    for (int i = 0; i < count; ++i) {
        settings.beginGroup("Limit_" + QString::number(i));

        SensorLimitsColored item;
        item.limit.min = settings.value("min", 0).toInt();
        item.limit.max = settings.value("max", 0).toInt();

        // Восстанавливаем цвет из HEX-строки
        item.color = QColor(settings.value("color").toString());
        if (!item.color.isValid()) {
            item.color = Qt::transparent; // Фолбек на случай ошибки
        }

        outData->detalaizedLimits->push_back(std::move(item));
        settings.endGroup();
    }

    settings.endGroup();
    return settings.status() == QSettings::NoError;
}
/** \brief Удаляет запись сенсора из INI, возвращает успех операции. */

bool SensorSettingsManager::removeSensor(const QString &sensorName) {
    QSettings settings(getConfigPath(), QSettings::IniFormat);

    settings.beginGroup("Sensors");
    settings.remove(sensorName);
    settings.endGroup();

    return settings.status() == QSettings::NoError;
}

