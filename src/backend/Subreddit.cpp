#include <QtCore/QCoreApplication>
#include "Subreddit.hpp"
Subreddit::Subreddit(const QString &name)
    : m_name(name),
      m_url("http://www.reddit.com/r/" + name + ".json")
{
    char *cargv = new char [1];
    int i = 1;
    QCoreApplication test(i, &cargv);

    FileDownloader downloader(m_url);
    QEventLoop wait;
    connect(&downloader, &FileDownloader::downloaded, &wait, &QEventLoop::quit);
    wait.exec();
    //qDebug() << downloader.downloadedData().toStdString().c_str();

    m_json = QJsonDocument().fromJson(downloader.downloadedData().toStdString().c_str());
}
QString Subreddit::getName()
{
    return m_name;
}
QJsonDocument Subreddit::getJson()
{
    return m_json;
}
