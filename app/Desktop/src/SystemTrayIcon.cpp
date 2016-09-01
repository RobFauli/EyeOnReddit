#include "SystemTrayIcon.hpp"

SystemTrayIcon::SystemTrayIcon(QSystemTrayIcon *parent) : QSystemTrayIcon(parent)
{

}

void SystemTrayIcon::initialize(QQmlApplicationEngine *engine)
{
    m_root = engine->rootObjects().at(0);

    QAction *minimizeAction = new QAction("Minimize to tray", m_root);
    m_root->connect(minimizeAction, SIGNAL(triggered()), m_root, SLOT(hide()));
    QAction *restoreAction = new QAction("Restore", m_root);
    m_root->connect(restoreAction, SIGNAL(triggered()), m_root, SLOT(showNormal()));
    QAction *quitAction = new QAction("Quit", m_root);
    m_root->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    
    QAction *clearAlertsAction = new QAction("Clear all alerts", m_root);
    auto redditView = engine->rootObjects()[0]->findChild<QObject*>(QStringLiteral("redditView"));
    m_root->connect(clearAlertsAction, SIGNAL(triggered()), redditView, SIGNAL(clearAllAlerts()));

    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addAction(clearAlertsAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    setContextMenu(trayIconMenu);
    setIcon(defaultIcon);

    connect(this, &QSystemTrayIcon::activated, this, &SystemTrayIcon::activatedSlot);
    connect(this, &QSystemTrayIcon::messageClicked, [this] () {
        auto window = dynamic_cast<QWindow*>(m_root);
        window->showNormal();
        window->raise();
        window->requestActivate();
    });
}

void SystemTrayIcon::setAlert(bool alert)
{
    if (m_alert != alert) {
        m_alert = alert;
        if (m_alert) {
            setIcon(alertIcon);
        } else {
            setIcon(defaultIcon);
        }
        emit alertChanged();
    } else {
    }
}

bool SystemTrayIcon::getAlert()
{
   return m_alert;
}

void SystemTrayIcon::receivePostAlert(Subreddit::AlertType type, const QString &subname, const QString &title)
{
    if (supportsMessages())
        showMessage("Important post(s) in /r/" + subname + ":", title);
}

void SystemTrayIcon::activatedSlot(QSystemTrayIcon::ActivationReason reason)
{
    auto window = dynamic_cast<QWindow*>(m_root);
    switch (reason) {
    case QSystemTrayIcon::ActivationReason::Unknown:
            break;
    case QSystemTrayIcon::ActivationReason::Context:
        break;
    case QSystemTrayIcon::ActivationReason::DoubleClick:
    case QSystemTrayIcon::ActivationReason::Trigger:
        window->showNormal();
        window->raise();
        window->requestActivate();
        break;
    case QSystemTrayIcon::ActivationReason::MiddleClick:
        break;
    }
}
