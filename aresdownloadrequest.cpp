#include "aresdownloadrequest.h"

AresDownloadRequest::AresDownloadRequest()
{
    sources = new QList<Source>();
}

AresDownloadRequest::~AresDownloadRequest()
{
    delete sources;
}

void AresDownloadRequest::setFileName(QString fileName){
    this->fileName = fileName;
}

void AresDownloadRequest::setHash(QString hash){
    this->hash = hash;
}

void AresDownloadRequest::setSize(long size){
    this->size = size;
}

QString AresDownloadRequest::getFileName(){
    return this->fileName;
}

QString AresDownloadRequest::getHash(){
    return this->hash;
}

long AresDownloadRequest::getSize(){
    return this->size;
}

void AresDownloadRequest::addSource(QString user, QString url){
    Source newSource;
    newSource.url = url;
    newSource.user = user;
    sources->append(newSource);
}

QList<AresDownloadRequest::Source> * AresDownloadRequest::getSources(){
    return sources;
}
