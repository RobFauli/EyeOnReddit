#ifndef SUBMONITOR_H
#define SUBMONITOR_H

#include <memory>
#include <QObject>
#include "Subreddit.hpp"

class SubMonitor : public QObject
{
    Q_OBJECT
public:
    //explicit SubMonitor(QObject *parent = 0);
    explicit SubMonitor(std::shared_ptr<Subreddit> &sub, QObject *parent = 0);

signals:
    void postWithHighCommentCount();
    void postWithHighScore();

private:
    std::shared_ptr<Subreddit> m_sub;
};

#endif // SUBMONITOR_H
