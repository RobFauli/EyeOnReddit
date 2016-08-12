#ifndef PHYSICSSANDBOX_FILEDOWNLOADER_HPP
#define PHYSICSSANDBOX_FILEDOWNLOADER_HPP


#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

// Stolen from https://wiki.qt.io/Download_Data_from_URL

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QUrl url, QObject *parent = 0);
    virtual ~FileDownloader();
    QByteArray downloadedData() const;

    signals:
    void downloaded();

private slots:
    void fileDownloaded(QNetworkReply* pReply);

private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
};


#endif //PHYSICSSANDBOX_FILEDOWNLOADER_HPP
