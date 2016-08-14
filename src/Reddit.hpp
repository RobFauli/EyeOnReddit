#ifndef REDDIT_HPP
#define REDDIT_HPP

#include "Subreddit.hpp"

#include <QObject>
#include <memory>

class Reddit : public QObject
{
    Q_OBJECT
public:
    explicit Reddit(QObject *parent = 0);
    void addSubreddit(std::shared_ptr<Subreddit> &sub);
    void addSubreddit(const QString &name);
    void removeSubreddit(Subreddit *const sub);
    void removeSubreddit(const QString &name);

    QVector<QString> getSubredditNames() const;

signals:

public slots:

private:
    QVector<std::shared_ptr<Subreddit>> m_subreddits;
};

#endif // REDDIT_HPP
