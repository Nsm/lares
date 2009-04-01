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
    AresDownload();
    void setFileName(QString fileName);
    void setHash(QString hash);
    void setSize(long size);
    void setTransmit(long transmit);
    void setState(State state);
    void setShared(bool shared);
    QString getFileName();
    QString getHash();
    long getSize();
    long getTransmit();
    AresDownload::State getState();
    bool isShared();

private:
    QString fileName;
    long size;
    long transmit;
    QString hash;
    State state;
    bool shared;
};

#endif // ARESDOWNLOAD_H
