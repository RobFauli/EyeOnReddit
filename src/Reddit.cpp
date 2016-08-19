#include "Reddit.hpp"

Reddit::Reddit(QObject *parent) : QObject(parent)
{

}

void Reddit::addSubreddit(const QString &name)
{
    if (name.size() == 0) {
    } else if (m_subreddits.contains(name)) {
        qDebug() << "Subreddit named " << name << " had already been added.";
    } else {
        m_subreddits[name] = std::make_shared<Subreddit>(name);
        qDebug() << "Subreddit named " << name << " has been added.";
    }
}

void Reddit::removeSubreddit(const QString &name)
{
    m_subreddits.remove(name);
}

QList<QString> Reddit::getSubredditNames() const
{
    return m_subreddits.keys();
}

QUrl Reddit::getSubredditUrl(const QString &name) const
{
    return m_subreddits[name]->getUrl();
}

Subreddit & Reddit::getSubreddit(const QString &name) const
{
    return *m_subreddits[name];
}
