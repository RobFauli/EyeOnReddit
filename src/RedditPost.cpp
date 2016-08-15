#include "RedditPost.hpp"

RedditPost::RedditPost(const QJsonObject &data, QObject *parent)
    : QObject(parent)
{
    addData(data);
}

void RedditPost::addData(const QJsonObject &data)
{
    m_data.insert(QDateTime::currentDateTimeUtc(), data);
}

QString RedditPost::getId()
{
    return m_data.last()["id"].toString();
}

QUrl RedditPost::getDomain()
{
    return m_data.last()["domain"].toString();
}

QString RedditPost::getTitle()
{
    return m_data.last()["title"].toString();
}

int RedditPost::getCommentCount()
{
    return m_data.last()["num_comments"].toInt();
}

int RedditPost::getScore()
{
    return m_data.last()["score"].toInt();
}
