#include "giftconnection.h"

GIftConnection::GIftConnection()
{
    tcpSocket = new QTcpSocket(this);
    buffer = "";
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readCommand()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(connectionError(QAbstractSocket::SocketError)));
}

void GIftConnection::open(QString host, int port ){
    //por las dudas de que la conexion ya esta abierta la cerramos
    tcpSocket->abort();
    tcpSocket->connectToHost(host,port);
}

void GIftConnection::close(){
    tcpSocket->close();
}

void GIftConnection::readCommand(){
    char character,prev_character = 0;

    while(tcpSocket->getChar(& character)){
        buffer += character;
        if(character == ';' && prev_character != '\\')
        {
            commandQueue.enqueue(new GIftCommand(buffer));
            buffer.clear();
            emit readyRead();
        }
        prev_character = character;
    }

}

void GIftConnection::connectionError(QAbstractSocket::SocketError){
    //TODO
}


GIftCommand * GIftConnection::read(){
    if(!commandQueue.isEmpty()){
        return commandQueue.dequeue();
    }else{
        return NULL ;
    }
}

void GIftConnection::write(GIftCommand * command){
    //TODO
}
