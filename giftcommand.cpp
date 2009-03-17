#include "giftcommand.h"

GIftCommand::GIftCommand()
{
}

GIftCommand::GIftCommand(QString protocolString)
{
    parseString(protocolString);
}

GIftCommand::GIftCommand(QString name, QString value, QString body)
{
    parseString(name,value,body);
}

bool GIftCommand::parseString(QString protocolString){
    QString element;
    QString name, value, body;
    protocolString = protocolString.trimmed();
    if(getElementType(element =getNextElement(protocolString)) == NAME){
        name = element;
    }else{
        //si el coamndo no comienza con su nombre entonces esta mal formado y no puede parsearse
        return false;
    }
    //el valor es opcional
    if(getElementType(element =getNextElement(protocolString)) == VALUE){
        value = element;
        element =getNextElement(protocolString);
    }
    if(protocolString.right(1) == ";"){
        body = element + protocolString.left(protocolString.size() - 2);
        return parseString(name,value,body);
    }else{
        return false;
    }
}

bool GIftCommand::parseString(QString name, QString value, QString body ){
    QString element;
    QString subelementName,subelementValue, subelementBody;
    this->name = name;
    this->value = value;
    element = getNextElement(body);
    while(element  != ""){
        if(getElementType(element) == NAME){
            subelementName = element;
            element =getNextElement(body);
            //el valor es opcional
            if(getElementType(element) == VALUE){
                subelementValue = element.mid(1,element.size() -2);
                element =getNextElement(body);
            }else{
                subelementValue = "";
            }
            if(getElementType(element) == BODY){
                subelementBody = element.mid(1,element.size() -2);
                element =getNextElement(body);
            }else{
                subelementBody = "";
            }
            subcomands[subelementName] = new GIftCommand(subelementName,subelementValue,subelementBody) ;
        }else{
            return false;
        }
    }
}

QString GIftCommand::getNextElement(QString &protocolString)
{
    protocolString = protocolString.trimmed();
    char closeTag = ' ';
    char openTag = ' ';
    uint actualPos = 0;
    uint openTagsCount = 0;
    QString result;
    if(protocolString[actualPos] == '('){
        closeTag = ')';
        openTag = '(';
        openTagsCount = 1;
    }
    else if(protocolString[actualPos] == '{'){
        closeTag = '}';
        openTag = '{';
        openTagsCount = 1;
    }

    for(; actualPos < protocolString.length(); actualPos++){
        if(openTagsCount == 0){
            if(protocolString[actualPos].isSpace() || protocolString[actualPos] == '(' || protocolString[actualPos] == '{' || protocolString[actualPos] == '}' || protocolString[actualPos] == ';')
                break;
        }
        else{
            if(protocolString[actualPos] == closeTag && protocolString[actualPos - 1] != '\\'){
                -- openTagsCount;
                if(openTagsCount == 0){
                    actualPos++;
                    break;
                }
            }
        }
    }
    //si no esta debidamente cerrado el elemento no se procesa.
    if(openTagsCount > 0)
        return QString("");
    result = protocolString.left(actualPos);
    protocolString = protocolString.mid(actualPos);
    return result;
}

GIftCommand::ElementType GIftCommand::getElementType(QString element){
    if(element[0] == '('){
        return VALUE;
    }else if(element[0] == '{'){
        return BODY;
    }else if(element[0] == ';'){
        return END;
    }else{
        return NAME;
    }

}
