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
    //agregar estadisticas de descarga, ingresa datos en cuanto a descarga/tiempo para poder calcular la velocidad de descarga()
    void addSpeedStat(long time, long size);

    //retorna la velocidad instantanea de bajada en bytes/segundos
    long getInstantSpeed();
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
    //velocidad instantanea de bajada en bytes/segundo
    long instantSpeed;
};

#endif // ARESDOWNLOAD_H
