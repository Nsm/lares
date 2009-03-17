#ifndef ARESCONNECTION_H
#define ARESCONNECTION_H

#include <QObject>

class AresConnection : public QObject
{
public:
    AresConnection();
    bool connect();
};

#endif // ARESCONNECTION_H
