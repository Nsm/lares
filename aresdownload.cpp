#include "aresdownload.h"

AresDownload::AresDownload()
{
}

AresDownload::AresDownload(int id)
{
    setId(id);
}

void AresDownload::setId(int id){
    this->id = id;
}

int AresDownload::getId(){
    return id;
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


void AresDownload::addSpeedStat(long time, long size){
    //se calcula la velocidad instantanea en bytes/segundo
    if(time){
        instantSpeed = size / (time * 1000);
    }
}

//retorna la velocidad instantanea de bajada en bytes/segundos
long AresDownload::getInstantSpeed(){
    return instantSpeed;
}

QString AresDownload::getFilePath(){
    //TODO las rutas a la carpeta de completados y de temporales deberian leerse de alguna clase de configuracion
    QString filePath = "";
    QString giFTDir = QDir::homePath() + "/.giFT";
    if(getState() == COMPLETED){
        filePath = giFTDir + "/completed/" + getFileName();
    }else{
        QDir tempDir(giFTDir + "/incoming");
        QStringList list = tempDir.entryList().filter(getFileName());
        if(list.length() > 0){
            filePath = tempDir.path() + "/" + list.first();
        }
    }
    return filePath;
}
