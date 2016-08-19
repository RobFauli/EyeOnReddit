#include "SystemTrayIcon.hpp"

SystemTrayIcon::SystemTrayIcon(QSystemTrayIcon *parent) : QSystemTrayIcon(parent)
{

}

void SystemTrayIcon::initialize(QQmlApplicationEngine *engine, const QIcon &icon)
{
    QObject *root = engine->rootObjects().at(0);

    QAction *minimizeAction = new QAction("Minimize to tray", root);
    root->connect(minimizeAction, SIGNAL(triggered()), root, SLOT(hide()));
    QAction *restoreAction = new QAction("Restore", root);
    root->connect(restoreAction, SIGNAL(triggered()), root, SLOT(showNormal()));
    QAction *quitAction = new QAction("Quit", root);
    root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    setContextMenu(trayIconMenu);
    setIcon(icon);
}
