#include "aresconnection.h"

AresConnection::AresConnection()
{
    giftConnection = new GIftConnection();
    connect(giftConnection, SIGNAL(readyRead()), this, SLOT(readCommand()));
    connectionStatus = DISCONNECTED;
}


void AresConnection::open(){
    this->setStatus(CONNECTING);
    GIftCommand * attachCommand = new GIftCommand("ATTACH","");
    giftConnection->open();
    attachCommand->setProperty("client","Lares");
    attachCommand->setProperty("version","0.1");
    attachCommand->setProperty("profile","lares");
    giftConnection->write(attachCommand);
    delete attachCommand;
}

/**
  Realiza una busqueda utilizando los criterios pasados como parametro y retorna el id de evento
  que permite unir la busqueda con los resultados de la misma
**/
int AresConnection::search(QString query){
    int eventId = giftConnection->getCurrentEventId();
    GIftCommand * searchCommand = new GIftCommand("SEARCH",QString::number(eventId));
    searchCommand->setProperty("query",query);
    giftConnection->write(searchCommand);
    delete searchCommand;
    return eventId;
}

void AresConnection::close(){
    giftConnection->close();
}

void AresConnection::readCommand(){
    GIftCommand * command;
    while((command = giftConnection->read())){
        if(command->getName() == "ATTACH" ){
            this->setStatus(CONNECT);
        }else if(command->getName() == "ITEM"){
            if(command->hasProperties()){
                AresItem * item = new AresItem();
                item->setUser(command->getProperty("user")->getValue());
                item->setNode(command->getProperty("node")->getValue());
                item->setAvailability(command->getProperty("availability")->getValue().toInt());
                item->setSize(command->getProperty("size")->getValue().toLong());
                item->setUrl(command->getProperty("url")->getValue());
                item->setFileName(command->getProperty("file")->getValue());
                item->setMimeType(command->getProperty("mime")->getValue());
                item->setHash(command->getProperty("hash")->getValue());
                emit itemFinded(item,command->getValue().toInt());
            }else{
                //un item sin contenido marca el final de una busqueda
                emit searchFinished(command->getValue().toInt());
            }
        }
    }
}

void AresConnection::setStatus(AresConnection::Status status){
    this->connectionStatus = status;
    emit statusChanged(status);
}

AresConnection::Status AresConnection::getStatus(){
    return connectionStatus;
}

void AresConnection::download(AresDownloadRequest request){
    foreach(AresDownloadRequest::Source source,*request.getSources()){
        GIftCommand * addSourceCommand = new GIftCommand("ADDSOURCE","");
        addSourceCommand->setProperty("url",source.url);
        addSourceCommand->setProperty("user",source.user);
        addSourceCommand->setProperty("hash",request.getHash());
        addSourceCommand->setProperty("size",QString::number(request.getSize()));
        addSourceCommand->setProperty("save",request.getFileName());
        giftConnection->write(addSourceCommand);
        delete addSourceCommand;
    }
}
