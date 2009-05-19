#include "giftconnection.h"

GIftConnection::GIftConnection()
{
    giftDaemon = new QProcess();
    tcpSocket = new QTcpSocket(this);
    buffer = "";
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readCommand()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(connectionError(QAbstractSocket::SocketError)));
}

/**
  Inicia el demonio de gift
**/
bool GIftConnection::startDaemon(){
    //inicia el demonio
    giftDaemon->start("giftd");
    //espera a que inicie un maximo de 5 segundos
    if(! giftDaemon->waitForStarted(5000)){
        //el demonio no inicio y ya paso el tiempo de espera maxima
        //TODO informar del error
        return false;
    }else{
        return true;
    }
}

/**
  Para al demonio de gift
**/
void GIftConnection::stopDaemon(){
    giftDaemon->terminate();
}


/**
  Abre la conexion con el servidor
**/
bool GIftConnection::open(QString host, int port ){
    //por las dudas de que la conexion ya esta abierta la cerramos
    tcpSocket->abort();
    //resetea el contador de ids de eventos
    setCurrentEventId(0);
    //se abre la conexion con el servidor
    tcpSocket->connectToHost(host,port);
    //se espera a que se establesca
    if(! tcpSocket->waitForConnected(3000)){
        //la conexion no se establecio y ya paso el tiempo maximo de espera
        //TODO informar del error
        return false;
    }else{
        if(tcpSocket->state() == QTcpSocket::ConnectedState){
            return true;
        }else{
            return false;
        }
    }

}

/**
  Cierra la conexion con el servidor
**/
void GIftConnection::close(){
    tcpSocket->close();
}

/**
  Funcion invocada cuando llega informacion desde el servidor.
  Se encarga de convertir los comandos a objetos GIftCommand y encolarlos en la commandQueue
**/
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

/**
  Funcion invocada cuando se produce un fallo en la conexion con el servidor
**/
void GIftConnection::connectionError(QAbstractSocket::SocketError){
    //TODO
}

/**
  Retorna los comandos enviados por el servidor o NULL en el caso de que no existan comandos nuevos para leer
**/
GIftCommand * GIftConnection::read(){
    if(!commandQueue.isEmpty()){
        return commandQueue.dequeue();
    }else{
        return NULL ;
    }
}

/**
  Envia un comando al servidor de giFt
**/
void GIftConnection::write(GIftCommand * command){
    if(tcpSocket->state() == QTcpSocket::ConnectedState){
        QString protocolString = command->toString();
        tcpSocket->write(protocolString.toLocal8Bit());
    }else{
        //TODO informar del error
    }
}

/**
  Retorna un id de evento unico para la session
  Los id se calculan sumando 1 al ultimo usado. De esta manera ningun pedido llevara el mismo id de evento
**/
int GIftConnection::getCurrentEventId(){
    currentEventId ++;
    return currentEventId;
}

/**
  Setea el id de evento actual, el proximo id que se calcule sera el actual + 1
**/
void GIftConnection::setCurrentEventId(int id){
    currentEventId = id;
}
