#include "Reddit.hpp"

Reddit::Reddit(QObject *parent) : QObject(parent)
{

}

void Reddit::addSubreddit(const QString &name)
{
    if (m_subreddits.contains(name))
        ;
    else
        m_subreddits[name] = std::make_shared<Subreddit>(name);
}

QList<QString> Reddit::getSubredditNames() const
{
    return m_subreddits.keys();
}

QUrl Reddit::getSubredditUrl(const QString &name)
{
    return m_subreddits[name]->getUrl();
}
