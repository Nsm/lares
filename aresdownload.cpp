#include "aresdownload.h"

AresDownload::AresDownload()
{
}

void AresDownload::setFileName(QString fileName){
    this->fileName = fileName;
}

void AresDownload::setHash(QString hash){
    this->hash = hash;
}

void AresDownload::setSize(long size){
    this->size = size;
}

void AresDownload::setTransmit(long transmit){
    this->transmit = transmit;
}

void AresDownload::setState(State state){
    this->state = state;
}

void AresDownload::setShared(bool shared){
    this->shared = shared;
}

QString AresDownload::getFileName(){
    return this->fileName;
}

QString AresDownload::getHash(){
    return this->hash;
}

long AresDownload::getSize(){
    return this->size;
}

long AresDownload::getTransmit(){
    return this->transmit;
}
AresDownload::State AresDownload::getState(){
    return this->state;
}

bool AresDownload::isShared(){
    return this->shared;
}
