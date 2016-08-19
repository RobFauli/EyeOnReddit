#ifndef SYSTEMTRAYICON_HPP
#define SYSTEMTRAYICON_HPP

#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>

#include <memory>



class SystemTrayIcon : public QSystemTrayIcon
{
public:
    explicit SystemTrayIcon(QSystemTrayIcon *parent = nullptr);
    explicit SystemTrayIcon(const QIcon &icon , QSystemTrayIcon *parent = nullptr);
    explicit SystemTrayIcon(QObject *engine, const QIcon &icon , QSystemTrayIcon *parent = nullptr);

    void initialize(QQmlApplicationEngine *engine, const QIcon &icon);
};

#endif // SYSTEMTRAYICON_HPP
