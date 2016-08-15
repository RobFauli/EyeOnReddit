#include "RedditSub.hpp"
RedditSub::RedditSub(const QString &name)
    : m_name(name),
      m_url("http://www.reddit.com/r/" + name + ".json")
{
    update();
}
QString RedditSub::getName() const
{
    return m_name;
}
QJsonDocument RedditSub::getJson() const
{
    return m_json;
}
QStringList RedditSub::getFrontpageTitles() const
{
    QStringList titles;
    Q_FOREACH(const QJsonValue post, getFrontpagePostsJsonArray()) {
        titles << preparepost(post)["title"].toString();
    }
    return titles;
}
const QJsonArray RedditSub::getFrontpagePostsJsonArray() const
{
    const QJsonValue data = m_json.object()["data"];
    const QJsonArray posts = data.toObject()["children"].toArray();
    return posts;
}

void RedditSub::populateFrontPagePosts()
{
    Q_FOREACH(const QJsonValue post, getFrontpagePostsJsonArray()) {
        const auto postObject = preparepost(post);
        const auto id = postObject["id"].toString();
        if (m_frontPagePosts.contains(id))
            m_frontPagePosts[id]->addData(postObject);
        else
            m_frontPagePosts.insert(postObject["id"].toString(), std::make_shared<RedditPost>(postObject));
    }
}
QVector<int> RedditSub::getFrontpageCommentCounts() const
{
    QVector<int> commentCounts;
    Q_FOREACH(const QJsonValue post, getFrontpagePostsJsonArray()) {
        commentCounts << preparepost(post)["num_comments"].toInt();
    }
    return commentCounts;
}
QVector<int> RedditSub::getFrontpageScores() const
{
    QVector<int> scores;
    Q_FOREACH(const QJsonValue post, getFrontpagePostsJsonArray()) {
        scores << preparepost(post)["score"].toInt();
    }
    return scores;
}
QList<QUrl> RedditSub::getFrontpageDomains() const
{
    QList<QUrl> domains;
    Q_FOREACH(const QJsonValue post, getFrontpagePostsJsonArray()) {
        domains << preparepost(post)["domain"].toString();
    }
    return domains;
}

void RedditSub::update()
{
    FileDownloader downloader(m_url);
    QEventLoop wait;
    connect(&downloader, &FileDownloader::downloaded, &wait, &QEventLoop::quit);
    wait.exec();

    m_json = QJsonDocument().fromJson(downloader.downloadedData().toStdString().c_str());
}
