#include "Reddit.hpp"

Reddit::Reddit(QObject *parent) : QObject(parent)
{

}

void Reddit::addSubreddit(const QString &name)
{
    // Should subreddits just be children of Reddit instead?
    if (name.size() == 0) {
    } else if (m_subreddits.contains(name)) {
        qDebug() << "Subreddit named " << name << " had already been added.";
    } else {
        m_subreddits[name] = std::make_shared<Subreddit>(name);

        connect(m_subreddits[name].get(), &Subreddit::postAlert,
                this, &Reddit::receivePostAlert);

        m_subreddits[name]->setUpdateIntervals(10000);

        // Avoid constructor call from QMLJS by setting ownership to C++
        QQmlEngine::setObjectOwnership(m_subreddits[name].get(),
                                       QQmlEngine::CppOwnership);
        emit subredditNamesChanged();

        qDebug() << "Subreddit named " << name << " has been added.";
    }
}

void Reddit::removeSubreddit(const QString &name)
{
    m_subreddits.remove(name);
    emit subredditNamesChanged();
}

QList<QString> Reddit::getSubredditNames() const
{
    return m_subreddits.keys();
}

QUrl Reddit::getSubredditUrl(const QString &name) const
{
    return m_subreddits[name]->getUrl();
}

bool Reddit::anyAlerts()
{
    bool state = false;
    Q_FOREACH(const auto &subreddit, m_subreddits) {
        if (subreddit->getImportantPosts().size() != 0) {
            state = true;
            break;
        }
    }
    return state;
}

Subreddit *Reddit::getSubreddit(const QString &name) const
{
    return m_subreddits[name].get();
}

void Reddit::receivePostAlert(Subreddit::AlertType type, const QString &subname, const QString &id)
{
    emit postAlertType(type, subname, id);
    emit postAlert(subname, id);
}
