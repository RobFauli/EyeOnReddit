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
    QString getPermalink();

    void setAlerted(bool alerted) { m_alerted = alerted; }
    bool getAlerted() { return m_alerted; }

    Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(QUrl domain READ getDomain NOTIFY domainChanged)
    Q_PROPERTY(int commentCount READ getCommentCount NOTIFY commentCountChanged)
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(QString permalink READ getPermalink NOTIFY permalinkChanged)

signals:
    void titleChanged();
    void domainChanged();
    void commentCountChanged();
    void scoreChanged();
    void permalinkChanged();

public slots:

private:
    QMap<QDateTime, QJsonObject> m_data;
    bool m_alerted = false;
};

#endif // REDDITPOST_HPP
