#ifndef REDDIT_HPP
#define REDDIT_HPP

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlField>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

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

    Q_INVOKABLE bool anyAlerts();

    Q_INVOKABLE Subreddit *getSubreddit(const QString &name) const;

    Q_PROPERTY(QList<QString> subredditNames
               READ getSubredditNames
               NOTIFY subredditNamesChanged)
    Q_PROPERTY(unsigned int initialUpdateInterval MEMBER m_defaultSubredditUpdateInterval
               NOTIFY initialUpdateIntervalChanged)

signals:
    void subredditNamesChanged();
    void postAlertType(Subreddit::AlertType type, const QString &subname, const QString &id);
    void postAlert(const QString &subname, const QString &id);
    void initialUpdateIntervalChanged();

public slots:
    void receivePostAlert(Subreddit::AlertType type, const QString &subname, const QString &id);

private:
    QMap<QString, std::shared_ptr<Subreddit>> m_subreddits;
    unsigned int m_defaultSubredditUpdateInterval = 60;
    QSqlDatabase db;
    QString m_AlertedTableName = "alerted";
};

#endif // REDDIT_HPP
