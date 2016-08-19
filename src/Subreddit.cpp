#include "RedditSub.hpp"
RedditSub::RedditSub(const QString &name)
    : m_name(name),
      m_url("http://www.reddit.com/r/" + name + ".json")
{
    connect(m_timer.get(), &QTimer::timeout, this, &RedditSub::update);
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
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        titles << post->getTitle();
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
    Q_FOREACH(const QJsonValue &post, getFrontpagePostsJsonArray()) {
        const auto postObject = preparepost(post);
        const auto id = postObject["id"].toString();
        if (m_frontPagePosts.contains(id)) {
            m_frontPagePosts[id]->addData(postObject);
        } else {
            m_frontPagePosts.insert(postObject["id"].toString(), std::make_shared<RedditPost>(postObject));
        }
    }
}
QVector<int> RedditSub::getFrontpageCommentCounts() const
{
    QVector<int> commentCounts;
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        commentCounts << post->getCommentCount();
    }
    return commentCounts;
}
QVector<int> RedditSub::getFrontpageScores() const
{
    QVector<int> scores;
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        scores << post->getScore();
    }
    return scores;
}
QList<QUrl> RedditSub::getFrontpageDomains() const
{
    QList<QUrl> domains;
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        domains << post->getDomain();
    }
    return domains;
}

void RedditSub::setUpdateIntervals(int milliseconds)
{
    m_timer->setInterval(milliseconds);
    m_timer->start();
}

void RedditSub::update()
{
    FileDownloader downloader(m_url);
    QEventLoop wait;
    connect(&downloader, &FileDownloader::downloaded, &wait, &QEventLoop::quit);
    wait.exec();

    m_json = QJsonDocument().fromJson(downloader.downloadedData().toStdString().c_str());
    populateFrontPagePosts();
    detectActivity();
}

void RedditSub::detectActivity()
{
    // Above average of X
    // X: Number of comments
    double numcom_avg
            = std::accumulate(
                m_frontPagePosts.cbegin(), m_frontPagePosts.cend(), 0,
                [](double x, std::shared_ptr<RedditPost> y) {return x + y->getCommentCount();})
            / m_frontPagePosts.size();
    Q_FOREACH(const auto &post, m_frontPagePosts)
        if (!(post->getAlerted()))
            if (post->getCommentCount() > (numcom_avg * m_thresholds.numCommentsFactor)) {
                emit postWithHighCommentCount(post->getId());
                post->setAlerted(true);
            }

    // X: Score
    double score_avg
            = std::accumulate(
                m_frontPagePosts.cbegin(), m_frontPagePosts.cend(), 0,
                [](double x, std::shared_ptr<RedditPost> y) {return x + y->getScore();})
            / m_frontPagePosts.size();
    Q_FOREACH(const auto &post, m_frontPagePosts)
        if (!(post->getAlerted()))
            if (post->getScore() > (score_avg * m_thresholds.scoreFactor)) {
                emit postWithHighScore(post->getId());
                post->setAlerted(true);
            }
}
