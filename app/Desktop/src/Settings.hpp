#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QtCore/QSettings>


class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(const QString &organization, const QString &application);

    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);
    Q_INVOKABLE QVariant value(const QString &key,
                               const QVariant &defaultValue = QVariant()) const;
    Q_INVOKABLE void sync() { QSettings::sync(); }
};
Q_DECLARE_METATYPE(Settings*)

#endif // SETTINGS_HPP
