#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include "SystemTrayIcon.hpp"

#include <QDebug>
#include "Reddit.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, "Systray",
                                 "Could not detect a system tray on this system.");
        return 1;
    }


    qmlRegisterType<Reddit>("myReddit", 0, 1, "Reddit");
    qmlRegisterUncreatableType<Subreddit>("myreddit", 0, 1, "Subreddit",
                                          "Cannot create Subreddits from QML.");
    qmlRegisterUncreatableType<RedditPost>("myReddit", 0, 1, "RedditPost",
                                           "Cannot create RedditPost from QML.");

    QQmlApplicationEngine engine;
    // Setup tray
    SystemTrayIcon tray;
    engine.rootContext()->setContextProperty("tray", &tray);

    Reddit reddit;
    QObject::connect(&reddit, &Reddit::postAlert,
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
    engine.rootContext()->setContextProperty("myReddit", &reddit);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    tray.initialize(&engine);
    tray.show();

    return app.exec();
}
