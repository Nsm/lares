#ifndef GIFTCONNECTION_H
#define GIFTCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QQueue>
#include "giftcommand.h"

class GIftConnection : public QObject
{
    Q_OBJECT
public:
    GIftConnection();
    static const int GIFT_PORT = 1213;
    void open(QString host = "localhost", int port = GIFT_PORT);
    void close();
    GIftCommand * read();
    void write(GIftCommand * command);
private:
    QTcpSocket *tcpSocket;
    QString buffer;
    QQueue<GIftCommand *> commandQueue;
private slots:
    void readCommand();
    void connectionError(QAbstractSocket::SocketError);
signals:
    void readyRead();
};

#endif // GIFTCONNECTION_H
