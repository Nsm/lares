#ifndef GIFTCOMMAND_H
#define GIFTCOMMAND_H

#include <QObject>
#include <QHash>

class GIftCommand : public QObject
{
public:
    //Constructores
    GIftCommand();
    GIftCommand(QString name, QString value);
    GIftCommand(QString protocolString);
    GIftCommand(QString name, QString value, QString body);

    bool parseString(QString protocolString);
    bool parseString(QString name, QString value, QString body );
    QString toString(bool subcommand = false);

    //Getters y Setters
    QString getName();
    void setName(QString name);

    QString getValue();
    void setValue(QString value);

    GIftCommand * getProperty(QString name);
    void setProperty(QString name, GIftCommand * value);
    void setProperty(QString name, QString value);

    bool hasProperty(QString name);
    bool hasProperties();

private:
    enum ElementType {NAME, VALUE, BODY};
    QHash<QString,GIftCommand*> subcommands;
    QString name;
    QString value;

    QString getNextElement(QString &protocolString);
    ElementType getElementType(QString element);

};

#endif // GIFTCOMMAND_H
