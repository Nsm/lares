#ifndef GIFTCONNECTION_H
#define GIFTCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QQueue>
#include <QProcess>
#include "giftcommand.h"

class GIftConnection : public QObject
{
    Q_OBJECT
public:
    GIftConnection();
    static const int GIFT_PORT = 1213;
    bool startDaemon();
    void stopDaemon();
    bool open(QString host = "localhost", int port = GIFT_PORT);
    void close();
    GIftCommand * read();
    void write(GIftCommand * command);
    int getCurrentEventId();
private:
    void setCurrentEventId(int id);
    QTcpSocket *tcpSocket;
    QString buffer;
    QQueue<GIftCommand *> commandQueue;
    QProcess * giftDaemon;
    int currentEventId;

private slots:
    void readCommand();
    void connectionError(QAbstractSocket::SocketError);
signals:
    void readyRead();
};

#endif // GIFTCONNECTION_H
