#ifndef SYSTEMTRAYICON_HPP
#define SYSTEMTRAYICON_HPP

#include <QtCore/QObject>
#include <QtGui/QWindow>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>

#include <memory>

#include "Subreddit.hpp"



class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QSystemTrayIcon *parent = nullptr);
    explicit SystemTrayIcon(const QIcon &icon , QSystemTrayIcon *parent = nullptr);
    explicit SystemTrayIcon(QObject *engine, const QIcon &icon , QSystemTrayIcon *parent = nullptr);

    void initialize(QQmlApplicationEngine *engine);

    Q_INVOKABLE void setAlert(bool m_alert);
    bool getAlert();

    Q_INVOKABLE void receivePostAlert(Subreddit::AlertType type, const QString &subname, const QString &id);

    Q_PROPERTY(bool alert READ getAlert WRITE setAlert NOTIFY alertChanged)

signals:
    void alertChanged();
    void clearAllAlerts();

public slots:
    void activatedSlot(QSystemTrayIcon::ActivationReason reason);

private:
    QIcon alertIcon = QIcon(":/assets/Icons/512x512/reddit_icon_red.png");
    QIcon defaultIcon = QIcon(":/assets/Icons/96x96/reddit_icon_circle.png");

    bool m_alert;

    QObject *m_root;
};

#endif // SYSTEMTRAYICON_HPP
