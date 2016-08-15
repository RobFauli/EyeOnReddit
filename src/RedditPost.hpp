#ifndef REDDITPOST_HPP
#define REDDITPOST_HPP

#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include <QObject>

class RedditPost : public QObject
{
    Q_OBJECT
public:
    explicit RedditPost(const QJsonObject &data, QObject *parent = 0);
    void addData(const QJsonObject &data);

    QString getId();
    QUrl getDomain();
    QString getTitle();
    int getCommentCount();
    int getScore();

signals:

public slots:

private:
    QMap<QDateTime, QJsonObject> m_data;
};

#endif // REDDITPOST_HPP
