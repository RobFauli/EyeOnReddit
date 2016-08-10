#include "Subreddit.hpp"
Subreddit::Subreddit(const QString &name)
    : m_name(name),
      m_url("http://www.reddit.com/r/" + name + ".json")
{

    FileDownloader downloader(m_url);
    QEventLoop wait;
    connect(&downloader, &FileDownloader::downloaded, &wait, &QEventLoop::quit);
    wait.exec();

    m_json = QJsonDocument().fromJson(downloader.downloadedData().toStdString().c_str());
}
QString Subreddit::getName() const
{
    return m_name;
}
QJsonDocument Subreddit::getJson() const
{
    return m_json;
}
QStringList Subreddit::getFrontpageTitles() const
{
    const QJsonValue data = m_json.object()["data"];
    const QJsonArray posts = data.toObject()["children"].toArray();

    QStringList titles;
    Q_FOREACH(const QJsonValue post, posts) {
        titles.push_back(post.toObject()["data"].toObject()["title"].toString());
    }

    return titles;
}
