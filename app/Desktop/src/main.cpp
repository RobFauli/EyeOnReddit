#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include "Settings.hpp"
#include "SystemTrayIcon.hpp"
#include "Reddit.hpp"

#ifdef QML_DESIGN
    class CacheManager : public QObject
    {
        Q_OBJECT
    public:
        CacheManager(QQmlEngine *engine) : m_engine(engine) { }
    public slots:
        void clear () {
            m_engine->clearComponentCache();
            qDebug() << "Engine cache cleared";
        }
    private:
        QQmlEngine *m_engine;
    };

#include "main.moc"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Settings settings("robfauli", "EyeOnReddit");
    
    // If there is no system tray, stop program immediately
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, "Systray",
                                 "Could not detect a system tray on this system.");
        return 1;
    }
    
    // Make types available in QML
    qmlRegisterType<Reddit>("myReddit", 0, 1, "Reddit");
    qmlRegisterUncreatableType<Subreddit>("myReddit", 0, 1, "Subreddit",
                                          "Cannot create Subreddits from QML.");
    qmlRegisterUncreatableType<RedditPost>("myReddit", 0, 1, "RedditPost",
                                           "Cannot create RedditPost from QML.");
    
    SystemTrayIcon tray;
    engine.rootContext()->setContextProperty("tray", &tray);
    Reddit reddit;
    engine.rootContext()->setContextProperty("theReddit", &reddit);
    engine.rootContext()->setContextProperty("settings", &settings);

    auto subnames = settings.value("subnames").toList();
    Q_FOREACH(const auto &subname, subnames)
        reddit.addSubreddit(subname.toString());

    QObject::connect(&reddit, &Reddit::postAlertType,
            [&tray, &reddit]
                     (Subreddit::AlertType type, const QString &subname,
                     const QString &id)
        {
            tray.setAlert(true);
            auto subreddit = reddit.getSubreddit(subname);
            auto post = subreddit->getPost(id);
            tray.receivePostAlert(type, subname, post->getTitle());
            subreddit->setPostImportantStatus(id, true);
        }
    );

    // Keep the followed subreddits in settings at all times in case of crash
    QObject::connect(&reddit, &Reddit::subredditNamesChanged,
                     [&reddit, &settings] () 
        {
            settings.setValue("subnames", QVariant(reddit.getSubredditNames()));
            settings.sync();
        }
    );

#ifndef QT_DEBUG
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#endif

#ifdef QT_DEBUG
    QString qmlFolder = "../../EyeOnReddit/app/Desktop/QML";
#ifdef QML_DESIGN
    engine.load(QUrl(qmlFolder + "/debugloader.qml"));
    auto loader = engine.rootObjects()[0];
    CacheManager trimer(&engine);
    QObject::connect(loader, SIGNAL(reloading()),
                     &trimer, SLOT(clear()));
#endif
#ifndef QML_DESIGN
    engine.load(QUrl(qmlFolder + "/main.qml"));
#endif
#endif
    
    // Warn the reddit view in QML about new posts
    auto redditView = engine.rootObjects()[0]->findChild<QObject*>(QStringLiteral("redditView"));
    QObject::connect(&reddit, SIGNAL(postAlert(QString,QString)), 
                     redditView, SIGNAL(postAlert(QString,QString)));

    tray.initialize(&engine);
    tray.show();

    return app.exec();
}
