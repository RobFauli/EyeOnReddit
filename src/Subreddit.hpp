#ifndef PHYSICSSANDBOX_SUBREDDIT_H
#define PHYSICSSANDBOX_SUBREDDIT_H

#include <QtCore/QObject>
#include <QtCore/QSet>
#include <QtCore/QVector>
#include <QtQml/QQmlEngine>
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
    enum class AlertType {
        X_TIMES_AVG_COMMENTS, X_TIMES_AVG_SCORE
    };
    Q_ENUM(AlertType)

    Subreddit(const QString &name);

    Q_INVOKABLE void setPostImportantStatus(const QString &id, bool important);

    QString getName() const;
    QUrl getUrl() const;
    QJsonDocument getJson() const;
    Q_INVOKABLE QStringList getFrontpageTitles() const;
    QVector<int> getFrontpageCommentCounts() const;
    QVector<int> getFrontpageScores() const;
    QList<QUrl> getFrontpageDomains() const;

    QList<QString> getImportantPosts() const;

    Q_INVOKABLE RedditPost* getPost(const QString &id) const;

    void setUpdateIntervals(int milliseconds);

    Q_PROPERTY(QStringList frontpageTitles READ getFrontpageTitles()
               NOTIFY frontpageTitlesChanged)
    Q_PROPERTY(QList<QUrl> frontpageDomains READ getFrontpageDomains()
               NOTIFY frontpageDomainsChanged)
    Q_PROPERTY(QVector<int> frontpageScores READ getFrontpageScores
               NOTIFY frontpageScoresChanged)
    Q_PROPERTY(QVector<int> frontpageCommentCounts READ getFrontpageCommentCounts
               NOTIFY frontpageCommentCountsChanged)

    Q_PROPERTY(QList<QString> importantPostIds READ getImportantPosts NOTIFY importantPostsChanged)

signals:
    void postAlert(AlertType type, const QString &subname, const QString &id);

    void frontpageTitlesChanged();
    void frontpageDomainsChanged();
    void frontpageScoresChanged();
    void frontpageCommentCountsChanged();

    void importantPostsChanged();

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
    QSet<QString> m_importantPosts; // Important posts that have not been seen or dismissed.
};

Q_DECLARE_METATYPE(Subreddit::AlertType)

inline QJsonObject preparepost(const QJsonValue &post)
{
    return post.toObject()["data"].toObject();
}

#endif //PHYSICSSANDBOX_SUBREDDIT_H
