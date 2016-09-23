#include "FileDownloader.hpp"

FileDownloader::FileDownloader(QUrl url, QObject *parent) :
    QObject(parent)
{
    connect(
        &m_WebCtrl, &QNetworkAccessManager::finished,
        this, &FileDownloader::fileDownloaded
    );

#ifdef QT_DEBUG
    if (QSslSocket::supportsSsl())
        qDebug() << "No SSL support detected.";
#endif

    QNetworkRequest request(url);
    m_WebCtrl.get(request);
}

FileDownloader::~FileDownloader() { }

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    m_DownloadedData = pReply->readAll();
    pReply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const {
    return m_DownloadedData;
}
