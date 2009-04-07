#ifndef ARESDOWNLOADUPDATE_H
#define ARESDOWNLOADUPDATE_H

#include "aresdownload.h"

class AresDownloadUpdate : public AresDownload
{
public:
    AresDownloadUpdate();
    void setThroughput(long throughput);
    void setElapsed(long elapsed);
    long getThroughput();
    long getElapsed();

private:
    long throughput;
    long elapsed;
};

#endif // ARESDOWNLOADUPDATE_H
