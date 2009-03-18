#ifndef GIFTCOMMAND_H
#define GIFTCOMMAND_H

#include <QObject>
#include <QHash>

class GIftCommand : public QObject
{
public:
    GIftCommand();
    GIftCommand(QString protocolString);
    GIftCommand(QString name, QString value, QString body);
    bool parseString(QString protocolString);
    bool parseString(QString name, QString value, QString body );
private:
    enum ElementType {NAME, VALUE, BODY};
    QHash<QString,GIftCommand*> subcomands;
    QString name;
    QString value;

    QString getNextElement(QString &protocolString);
    ElementType getElementType(QString element);

};

#endif // GIFTCOMMAND_H
