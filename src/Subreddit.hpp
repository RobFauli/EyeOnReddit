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

struct Thresholds {
    double numCommentsFactor = 3.0;
    double scoreFactor = 3.0;
};

class Subreddit : public QObject
{
    Q_OBJECT
public:
    Subreddit(const QString &name);

    QString getName() const;
    QUrl getUrl() const;
    QJsonDocument getJson() const;
    Q_INVOKABLE QStringList getFrontpageTitles() const;
    QVector<int> getFrontpageCommentCounts() const;
    QVector<int> getFrontpageScores() const;
    QList<QUrl> getFrontpageDomains() const;

    void setUpdateIntervals(int milliseconds);

    Q_PROPERTY(QStringList frontpageTitles
               READ getFrontpageTitles()
               NOTIFY frontpageTitlesChanged)
    Q_PROPERTY(QList<QUrl> frontpageDomains
               READ getFrontpageDomains()
               NOTIFY frontpageDomainsChanged)
    Q_PROPERTY(QVector<int> frontpageScores
               READ getFrontpageScores
               NOTIFY frontpageScoresChanged)
    Q_PROPERTY(QVector<int> frontpageCommentCounts
               READ getFrontpageCommentCounts
               NOTIFY frontpageCommentCountsChanged)

signals:
    void postWithHighCommentCount(QString id);
    void postWithHighScore(QString id);

    void frontpageTitlesChanged();
    void frontpageDomainsChanged();
    void frontpageScoresChanged();
    void frontpageCommentCountsChanged();

public slots:
    void update();

protected:
    Subreddit() {} // Needs a ctor with no args to register as QML type.

private:
    void detectActivity();

    QString m_name;
    QUrl m_url;
    QJsonDocument m_json;
    const QJsonArray getFrontpagePostsJsonArray() const;
    void populateFrontPagePosts();

    QMap<QString, std::shared_ptr<RedditPost>> m_frontPagePosts; // Keyed by unique ID

    std::unique_ptr<QTimer> m_timer;

    Thresholds m_thresholds;
};

inline QJsonObject preparepost(const QJsonValue &post)
{
    return post.toObject()["data"].toObject();
}

#endif //PHYSICSSANDBOX_SUBREDDIT_H
