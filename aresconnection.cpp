#include "aresconnection.h"

AresConnection::AresConnection()
{
    giftConnection = new GIftConnection();
    connect(giftConnection, SIGNAL(readyRead()), this, SLOT(readCommand()));
    connectionStatus = DISCONNECTED;
}

/**
  Abre la copnexion con el demonio de giFT
**/
void AresConnection::open(){
    //se cambia el estado a conectando
    this->setStatus(CONNECTING);
    //se inicia el demonio de gift
    if(giftConnection->startDaemon()){
        bool connectionOpened = false;
        int reattempts = 0;
        //se abre la conexion
        connectionOpened = giftConnection->open();
        while(!(connectionOpened) && (reattempts < 3)){
            //si no se pudo conectar se espera y se intenta de nuevo ya que gift a veces tarda un tiempo hasta que se incializa y abre el puerto
            reattempts ++;
            sleep(2);
            connectionOpened = giftConnection->open();
        }
        if(connectionOpened){
            // y se envia un comando de attach al servidor
            GIftCommand * attachCommand = new GIftCommand("ATTACH","");
            attachCommand->setProperty("client","Lares");
            attachCommand->setProperty("version","0.1");
            attachCommand->setProperty("profile","lares");
            giftConnection->write(attachCommand);
            delete attachCommand;
        }else{
            //la conexion no se pudo establecer con el demonio
            //TODO informar del error
        }
    }else{
        //no se pudo iniciar el demonio
        //TODO informar del error
    }
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
    giftConnection->stopDaemon();
}

void AresConnection::readCommand(){
    GIftCommand * command;
    while((command = giftConnection->read())){
        if(command->getName() == "ATTACH" ){
            this->setStatus(CONNECT);
        }else if(command->getName() == "ITEM"){
            newSearchedItem(command);
        }else if(command->getName() == "ADDDOWNLOAD"){
            newDownload(command);
        }else if(command->getName() == "CHGDOWNLOAD"){
            updateDownload(command);
        }else if(command->getName() == "DELDOWNLOAD"){
            downloadFinished(command->getValue().toInt());
        }
    }
}

void AresConnection::newSearchedItem(GIftCommand * command){
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

        //se chequea el item que se encontro corresponde a una descarga ya inciada. Si es asi se lo agrega como fuente a esa descarga. Esto hace que se aprobechen todas las fuentes encontradas
        if(downloadHash.contains(item->getHash())){
            addSource(downloadHash[item->getHash()]->getId(),item->getUrl(),item->getUser());
        }

        emit itemFinded(item,command->getValue().toInt());
    }else{
        //un item sin contenido marca el final de una busqueda
        emit searchFinished(command->getValue().toInt());
    }
}

void AresConnection::newDownload(GIftCommand * command){
    AresDownload * download = new AresDownload();
    download->setId(command->getValue().toInt());
    download->setSize(command->getProperty("size")->getValue().toLong());
    download->setFileName(command->getProperty("file")->getValue());
    download->setHash(command->getProperty("hash")->getValue());
    download->setTransmit(command->getProperty("transmit")->getValue().toLong());
    QString state = command->getProperty("state")->getValue().toLower();
    if(state == "active"){
        download->setState(AresDownload::ACTIVE);
    }else if(state == "completed"){
        download->setState(AresDownload::COMPLETED);
    }else if(state == "paused"){
        download->setState(AresDownload::PAUSED);
    }
    downloads.insert(download->getId(),download);
    downloadHash.insert(download->getHash(),download);
    emit downloadStarted(download);
}

void AresConnection::updateDownload(GIftCommand * command){
    int downloadId = command->getValue().toInt();
    //chequeamos si existe la descarga a la cual se refiere la actualizacion. (se supone que tiene que existir)
    if(downloads.contains(downloadId)){
        AresDownload * download = downloads[downloadId];
        download->setTransmit(command->getProperty("transmit")->getValue().toLong());
        QString state = command->getProperty("state")->getValue().toLower();
        if(state == "active"){
            download->setState(AresDownload::ACTIVE);
        }else if(state == "completed"){
            download->setState(AresDownload::COMPLETED);
        }else if(state == "paused"){
            download->setState(AresDownload::PAUSED);
        }
        download->addSpeedStat(command->getProperty("elapsed")->getValue().toLong(),command->getProperty("throughput")->getValue().toLong());
        emit downloadChanged(downloadId);
    }
}

void AresConnection::downloadFinished(int downloadId){
    if(downloads.contains(downloadId)){
       if(downloads[downloadId]->getState() == AresDownload::COMPLETED){
           emit downloadCompleted(downloadId);
       }else{
           downloads[downloadId]->setState(AresDownload::CANCELLED);
           emit downloadCancelled(downloadId);
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

void AresConnection::download(AresDownloadRequest * request){
    foreach(AresDownloadRequest::Source source,*request->getSources()){
        GIftCommand * addSourceCommand = new GIftCommand("ADDSOURCE","");
        addSourceCommand->setProperty("url",source.url);
        addSourceCommand->setProperty("user",source.user);
        addSourceCommand->setProperty("hash",request->getHash());
        addSourceCommand->setProperty("size",QString::number(request->getSize()));
        addSourceCommand->setProperty("save",request->getFileName());
        giftConnection->write(addSourceCommand);
        delete addSourceCommand;
    }
}

void AresConnection::addSource(int downloadId,QString url,QString user){
    if(downloads.contains(downloadId)){
        AresDownload * download = downloads[downloadId];
        GIftCommand * addSourceCommand = new GIftCommand("ADDSOURCE","");
        addSourceCommand->setProperty("url",url);
        addSourceCommand->setProperty("user",user);
        addSourceCommand->setProperty("hash",download->getHash());
        addSourceCommand->setProperty("size",QString::number(download->getSize()));
        addSourceCommand->setProperty("save",download->getFileName());
        giftConnection->write(addSourceCommand);
        delete addSourceCommand;
    }
}

void AresConnection::cancelSearch(int searchId){
    GIftCommand * cancelCommand = new GIftCommand("SEARCH",QString::number(searchId));
    cancelCommand->setProperty("action","cancel");
    giftConnection->write(cancelCommand);
    delete cancelCommand;
}

void AresConnection::cancelDownload(int downloadId){
    GIftCommand * cancelCommand = new GIftCommand("TRANSFER",QString::number(downloadId));
    cancelCommand->setProperty("action","cancel");
    giftConnection->write(cancelCommand);
    delete cancelCommand;
}

void AresConnection::pauseDownload(int downloadId){
    GIftCommand * cancelCommand = new GIftCommand("TRANSFER",QString::number(downloadId));
    cancelCommand->setProperty("action","pause");
    giftConnection->write(cancelCommand);
    delete cancelCommand;
}

void AresConnection::unpauseDownload(int downloadId){
    GIftCommand * cancelCommand = new GIftCommand("TRANSFER",QString::number(downloadId));
    cancelCommand->setProperty("action","unpause");
    giftConnection->write(cancelCommand);
    delete cancelCommand;
}

void AresConnection::deleteDownload(int downloadId){
    if(downloads.contains(downloadId)){
        AresDownload * download = downloads[downloadId];
        //si la descarga aun no se completo ni estaba cancelada entonces se cancela
        if(download->getState() != AresDownload::COMPLETED && download->getState() != AresDownload::CANCELLED){
            cancelDownload(downloadId);
        }
        downloads.remove(downloadId);
        downloadHash.remove(download->getHash());
        delete download;
    }
}

AresDownload * AresConnection::getDownload(int downloadId){
    if(downloads.contains(downloadId)){
        return downloads[downloadId];
    }else{
        return NULL;
    }
}
