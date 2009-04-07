#ifndef ARESDOWNLOAD_H
#define ARESDOWNLOAD_H

#include <QObject>
#include <QList>

class AresDownload : public QObject
{
public:
    enum State{
        ACTIVE, PAUSED, COMPLETED
    };

    struct Source{
        QString user;
        QString url;
        QString status;
        long start;
        long total;
    };
//    Faltan metodos getters y setters para los sources

    AresDownload();
    AresDownload(int id);
    void setFileName(QString fileName);
    void setHash(QString hash);
    void setSize(long size);
    void setTransmit(long transmit);
    void setState(State state);
    void setShared(bool shared);
    void setId(int id);

    QString getFileName();
    QString getHash();
    long getSize();
    long getTransmit();
    AresDownload::State getState();
    bool isShared();
    int getId();

private:
    int id;
    QString fileName;
    long size;
    long transmit;
    QString hash;
    State state;
    bool shared;
};

#endif // ARESDOWNLOAD_H
