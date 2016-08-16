#ifndef REDDITPOST_HPP
#define REDDITPOST_HPP

#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QUrl>

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

    void setAlerted(bool alerted) { m_alerted = alerted; }
    bool getAlerted() { return m_alerted; }

signals:

public slots:

private:
    QMap<QDateTime, QJsonObject> m_data;
    bool m_alerted = false;
};

#endif // REDDITPOST_HPP
