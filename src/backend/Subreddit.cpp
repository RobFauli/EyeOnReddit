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
    QStringList titles;
    Q_FOREACH(const QJsonValue post, getFrontpagePostJsonObjects()) {
        titles << preparepost(post)["title"].toString();
    }
    return titles;
}
const QJsonArray Subreddit::getFrontpagePostJsonObjects() const
{
    const QJsonValue data = m_json.object()["data"];
    const QJsonArray posts = data.toObject()["children"].toArray();
    return posts;
}
QVector<int> Subreddit::getFrontpageCommentCounts() const
{
    QVector<int> commentCounts;
    Q_FOREACH(const QJsonValue post, getFrontpagePostJsonObjects()) {
        commentCounts << preparepost(post)["num_comments"].toInt();
    }
    return commentCounts;
}
QVector<int> Subreddit::getFrontpageScores() const
{
    QVector<int> scores;
    Q_FOREACH(const QJsonValue post, getFrontpagePostJsonObjects()) {
        scores << preparepost(post)["score"].toInt();
    }
    return scores;
}
QList<QUrl> Subreddit::getFrontpageDomains() const
{
    QList<QUrl> domains;
    Q_FOREACH(const QJsonValue post, getFrontpagePostJsonObjects()) {
        domains << preparepost(post)["domain"].toString();
    }
    return domains;
}
