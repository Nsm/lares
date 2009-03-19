#include "aresitem.h"

AresItem::AresItem()
{
}

QString AresItem::getUser(){
    return user;
}
QString AresItem::getNode(){
    return node;
}
QString AresItem::getUrl(){
    return url;
}
QString AresItem::getFileName(){
    return fileName;
}
QString AresItem::getMimeType(){
    return mimeType;
}
QString AresItem::getHash(){
    return hash;
}
int AresItem::getAvailability(){
    return availability;
}
long AresItem::getSize(){
    return size;
}
void AresItem::setUser(QString user){
    this->user = user;
}
void AresItem::setNode(QString node){
    this->node = node;
}
void AresItem::setUrl(QString url){
    this->url = url;
}
void AresItem::setFileName(QString fileName){
    this->fileName = fileName;
}
void AresItem::setMimeType(QString mimeType){
    this->mimeType = mimeType;
}
void AresItem::setHash(QString hash){
    this->hash = hash;
}
void AresItem::setAvailability(int availability){
    this->availability = availability;
}
void AresItem::setSize(long size){
    this->size = size;
}
