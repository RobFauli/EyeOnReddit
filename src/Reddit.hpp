#ifndef REDDIT_HPP
#define REDDIT_HPP

#include <QtCore/QObject>

#include <memory>

#include "Subreddit.hpp"

class Reddit : public QObject
{
    Q_OBJECT
public:
    explicit Reddit(QObject *parent = 0);

    Q_INVOKABLE void addSubreddit(const QString &name);
    Q_INVOKABLE void removeSubreddit(const QString &name);

    QList<QString> getSubredditNames() const;

    Q_INVOKABLE QUrl getSubredditUrl(const QString &name) const;

    Q_INVOKABLE Subreddit *getSubreddit(const QString &name) const;

    Q_PROPERTY(QList<QString> subredditNames
               READ getSubredditNames
               NOTIFY namesChanged)

signals:
    void namesChanged();

public slots:

private:
    QMap<QString, std::shared_ptr<Subreddit>> m_subreddits;
};

#endif // REDDIT_HPP
