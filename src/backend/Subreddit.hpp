#ifndef PHYSICSSANDBOX_SUBREDDIT_H
#define PHYSICSSANDBOX_SUBREDDIT_H

#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include "FileDownloader.hpp"

class Subreddit : public QObject
{
    Q_OBJECT
public:
    Subreddit(const QString &name);

    QString getName();
    QJsonDocument getJson();

private:
    QString m_name;
    QUrl m_url;
    QJsonDocument m_json;
};


#endif //PHYSICSSANDBOX_SUBREDDIT_H
