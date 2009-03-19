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
}

void AresConnection::close(){
    giftConnection->close();
}

void AresConnection::readCommand(){
    GIftCommand * command;
    while((command = giftConnection->read())){
        if(command->getName() == "ATTACH" ){
            this->setStatus(CONNECT);
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
