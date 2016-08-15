#ifndef PHYSICSSANDBOX_SUBREDDIT_H
#define PHYSICSSANDBOX_SUBREDDIT_H

#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <memory>
#include "FileDownloader.hpp"
#include "RedditPost.hpp"

class RedditSub : public QObject
{
    Q_OBJECT
public:
    RedditSub(const QString &name);

    QString getName() const;
    QJsonDocument getJson() const;
    QStringList getFrontpageTitles() const;
    QVector<int> getFrontpageCommentCounts() const;
    QVector<int> getFrontpageScores() const;
    QList<QUrl> getFrontpageDomains() const;

signals:
    void postWithHighCommentCount();
    void postWithHighScore();

public slots:
    void update();

private:
    void detectActivity();

    QString m_name;
    QUrl m_url;
    QJsonDocument m_json;
    const QJsonArray getFrontpagePostsJsonArray() const;
    void populateFrontPagePosts();

    QMap<QString, std::shared_ptr<RedditPost>> m_frontPagePosts; // Keyed by unique ID
    std::unique_ptr<QTimer> m_timer;
};

inline QJsonObject preparepost(const QJsonValue &post)
{
    return post.toObject()["data"].toObject();
}

#endif //PHYSICSSANDBOX_SUBREDDIT_H
