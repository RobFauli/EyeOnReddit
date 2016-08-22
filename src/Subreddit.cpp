#include "Subreddit.hpp"
Subreddit::Subreddit(const QString &name)
    : m_name(name),
      m_url("http://www.reddit.com/r/" + name),
      m_timer(std::make_unique<QTimer>())
{
    connect(m_timer.get(), &QTimer::timeout, this, &Subreddit::update);
    update();
}
QString Subreddit::getName() const
{
    return m_name;
}

QUrl Subreddit::getUrl() const
{
    return m_url;
}
QJsonDocument Subreddit::getJson() const
{
    return m_json;
}
QStringList Subreddit::getFrontpageTitles() const
{
    QStringList titles;
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        titles << post->getTitle();
    }
    return titles;
}
const QJsonArray Subreddit::getFrontpagePostsJsonArray() const
{
    const QJsonValue data = m_json.object()["data"];
    const QJsonArray posts = data.toObject()["children"].toArray();
    return posts;
}

void Subreddit::populateFrontPagePosts()
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
QVector<int> Subreddit::getFrontpageCommentCounts() const
{
    QVector<int> commentCounts;
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        commentCounts << post->getCommentCount();
    }
    return commentCounts;
}
QVector<int> Subreddit::getFrontpageScores() const
{
    QVector<int> scores;
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        scores << post->getScore();
    }
    return scores;
}
QList<QUrl> Subreddit::getFrontpageDomains() const
{
    QList<QUrl> domains;
    Q_FOREACH(const auto &post, m_frontPagePosts) {
        domains << post->getDomain();
    }
    return domains;
}

RedditPost* Subreddit::getPost(const QString &id) const
{
    QQmlEngine::setObjectOwnership(m_frontPagePosts[id].get(),
                                   QQmlEngine::CppOwnership);
    return m_frontPagePosts[id].get();
}

void Subreddit::setUpdateIntervals(int milliseconds)
{
    m_timer->setInterval(milliseconds);
    m_timer->start();
}

void Subreddit::update()
{
    FileDownloader downloader(m_url.toString() + "/hot/.json");
    QEventLoop wait;
    connect(&downloader, &FileDownloader::downloaded, &wait, &QEventLoop::quit);
    wait.exec();

    m_json = QJsonDocument().fromJson(downloader.downloadedData().toStdString().c_str());
    populateFrontPagePosts();
    if (m_timer->isActive())
        detectActivity();
}

void Subreddit::detectActivity()
{
    if (m_frontPagePosts.size() > 15) {
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
                    emit postAlert(AlertType::X_TIMES_AVG_COMMENTS, m_name, post->getId());
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
                    emit postAlert(AlertType::X_TIMES_AVG_SCORE, m_name, post->getId());
                    post->setAlerted(true);
                }
    } else {
    }
}
