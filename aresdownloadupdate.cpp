#include "aresdownloadupdate.h"

AresDownloadUpdate::AresDownloadUpdate()
{
}

void AresDownloadUpdate::setThroughput(long throughput){
    this->throughput = throughput;
}

void AresDownloadUpdate::setElapsed(long elapsed){
    this->elapsed = elapsed;
}

long AresDownloadUpdate::getThroughput(){
    return throughput;
}

long AresDownloadUpdate::getElapsed(){
    return elapsed;
}
