#ifndef PHYSICSSANDBOX_SUBREDDIT_H
#define PHYSICSSANDBOX_SUBREDDIT_H

#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "FileDownloader.hpp"

class Subreddit : public QObject
{
    Q_OBJECT
public:
    Subreddit(const QString &name);

    QString getName() const;
    QJsonDocument getJson() const;
    QStringList getFrontpageTitles() const;
    QVector<int> getFrontpageCommentCounts() const;
    QVector<int> getFrontpageScores() const;
    QList<QUrl> getFrontpageDomains() const;

signals:
    void postWithHighCommentCount();
    void postWithHighScore();

private:
    QString m_name;
    QUrl m_url;
    QJsonDocument m_json;
    const QJsonArray getFrontpagePostJsonObjects() const;

    std::shared_ptr<Subreddit> m_sub;
    std::unique_ptr<QTimer> m_timer;
};

inline QJsonObject preparepost(const QJsonValue &post)
{
    return post.toObject()["data"].toObject();
}

#endif //PHYSICSSANDBOX_SUBREDDIT_H
