#include "Reddit.hpp"

Reddit::Reddit(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "default");
    db.setDatabaseName("Reddit.sqlite");
    if (!db.isOpen())
        db.open();
    if (!db.tables().contains(m_AlertedTableName)) {
        QSqlQuery query(db);
        query.prepare("CREATE TABLE " + m_AlertedTableName + " "
                        "(id string primare key, subname string)");
        query.exec();
        qDebug() << "Added alerted table to db.";
        qDebug() << "The tables are now: " << db.tables();
    }
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

        m_subreddits[name]->setUpdateIntervals(m_defaultSubredditUpdateInterval);

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
    QSqlTableModel model(Q_NULLPTR, db);
    model.setTable(m_AlertedTableName);
    model.setFilter("id='" + id + "'");
    model.select();
    if (model.record(0).value(0).toString() == "") {
        emit postAlertType(type, subname, id);
        emit postAlert(subname, id);
        QSqlRecord record;
        record.append(QSqlField("id", QVariant::String));
        record.append(QSqlField("subname", QVariant::String));
        record.setValue("id", id);
        record.setValue("subname", subname);
        model.setTable(m_AlertedTableName);
        model.select();
        model.insertRecord(-1, record);
    } else {
        qDebug() << "Post " + id + " had already been alerted.";
    }
}
