#ifndef ARESITEM_H
#define ARESITEM_H

#include <QObject>

class AresItem : public QObject
{
public:
    AresItem();
    QString getUser();
    QString getNode();
    QString getUrl();
    QString getFileName();
    QString getMimeType();
    QString getHash();
    int getAvailability();
    long getSize();
    void setUser(QString user);
    void setNode(QString node);
    void setUrl(QString url);
    void setFileName(QString fileName);
    void setMimeType(QString mimeType);
    void setHash(QString hash);
    void setAvailability(int availability);
    void setSize(long size);
private:
    QString user;
    QString node;
    int availability;
    long size;
    QString url;
    QString fileName;
    QString mimeType;
    QString hash;
};

#endif // ARESITEM_H
