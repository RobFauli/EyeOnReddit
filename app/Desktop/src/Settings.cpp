#include "Settings.hpp"

Settings::Settings(const QString &organization, const QString &application)
    : QSettings(organization, application)
{
}

void Settings::setValue(const QString &key, const QVariant &value)
{
    QSettings::setValue(key, value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue) const
{
    return QSettings::value(key, defaultValue);
}
