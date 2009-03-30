#ifndef ARESDOWNLOADREQUEST_H
#define ARESDOWNLOADREQUEST_H

#include <QObject>
#include <QList>
class AresDownloadRequest : public QObject
{
public:
    struct Source{
        QString user;
        QString url;
    };
    AresDownloadRequest();
    ~AresDownloadRequest();
    void setFileName(QString fileName);
    void setHash(QString hash);
    void setSize(long size);
    QString getFileName();
    QString getHash();
    long getSize();
    void addSource(QString user, QString url);
    QList<Source> * getSources();
private:
    QString fileName;
    long size;
    QString hash;
    QList<Source> * sources;
};

#endif // ARESDOWNLOADREQUEST_H
