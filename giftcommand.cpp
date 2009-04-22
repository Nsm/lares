/**
  Cada objeto GIftCommand representa un comando dentro de la comunicacion con el servidor de GIft.
  Esta clase permite tanto parsear el string de un comando entrante para convertirlo en un objeto GIftCommand,
  como obtener el string del protocolo correspondiente a un objeto para poder enviarlo al servidor.
  Un comando ademas de un nombre y un valor, puede contener subcomandos.
  (No se diferencia entre CLAVE y SUBCOMANDO como los describe la documentacion ya que se considera que una clave es tan solo
  un tipo especial de subcomando que no contiene otros subcomandos)
**/
#include "giftcommand.h"

GIftCommand::GIftCommand()
{
}

GIftCommand::GIftCommand(QString name, QString value)
{
    setName(name);
    setValue(value);
}

/**
  Construye un objeto que representa a un comando GIft a partir de un string conteninedo el comando como lo espesifica el protocolo.
*/
GIftCommand::GIftCommand(QString protocolString)
{
    parseString(protocolString);
}

/**
  Construye un objeto que representa a un comando GIft a partir de su nombre, valor un string conteninedo el cuerpo del comando como lo espesifica el protocolo.
*/
GIftCommand::GIftCommand(QString name, QString value, QString body)
{
    parseString(name,value,body);
}

/**
 * Parsea un string conteniendo un comando completo del protocolo de comunicacion con GIft.
 * A partir del string se obtienen los datos del objeto que representan al comando.
 */
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
        value = element.mid(1,element.size() -2);
        element =getNextElement(protocolString);
    }
    if(protocolString.right(1) == ";"){
        body = element + protocolString.left(protocolString.size() - 2);
        return parseString(name,value,body);
    }else{
        return false;
    }
}

/**
 * Realiza el parseo de un comando del protocolo de comunicacion con GIft ya dividido en nombre del comando, valor y cuerpo.
 * A partir del string se obtienen los datos del objeto que representan al comando.
 */
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
            subcommands[subelementName] = new GIftCommand(subelementName,subelementValue,subelementBody) ;
        }else{
            return false;
        }
    }
    return true;
}

/**
* Esta funcion facilita el parseo de comandos, retornando los elementos del comando.
* Un elemento puede ser un nombre de comando, un valor (encerrado entre parentesis en el protocolo) o
* un cuerpo de comando (encerrado entre llaves en el protocolo).
* El elemento retornado es quitado del string de entrada.
*/
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

/**
* Retorna el tipo de elemento pasado como parametro.
* Un elemento puede ser un nombre de comando, un valor (encerrado entre parentesis en el protocolo) o
* un cuerpo de comando (encerrado entre llaves en el protocolo).
* Esta funcion facilita el parseo de comandos.
*/
GIftCommand::ElementType GIftCommand::getElementType(QString element){
    if(element[0] == '('){
        return VALUE;
    }else if(element[0] == '{'){
        return BODY;
    }else{
        return NAME;
    }

}

QString GIftCommand::getName(){
    return name;
}

void GIftCommand::setName(QString name){
    this->name = name;
}

QString GIftCommand::getValue(){
    return value;
}

void GIftCommand::setValue(QString value){
    this->value = value;
}

/*
  Retorna la propiedad (subcomando) con el nombre correspondiente. En caso de no existir ninguna retorna NULL
*/
GIftCommand * GIftCommand::getProperty(QString name){
    if(subcommands.contains(name)){
        return subcommands[name];
    }else{
        return NULL;
    }
}

void GIftCommand::setProperty(QString name, GIftCommand * value){
    subcommands[name] = value;
}

void GIftCommand::setProperty(QString name, QString value){
    subcommands[name] =  new GIftCommand(name,value);
}

bool GIftCommand::hasProperty(QString name){
    return subcommands.contains(name);
}

bool GIftCommand::hasProperties(){
    return !subcommands.isEmpty();
}

/**
  Obtiene el string del protocolo correspondiente al objeto para poder enviarlo al servidor.
  El parametro subcommand indica si debe codificarse como comando (false) o como subcomando(true)
**/
QString GIftCommand::toString(bool subcommand){
    QString result;
    result = name.toUpper() + " ";
    if(!value.isEmpty()){
        result += "(" + value + ")";
    }
    if(!subcommands.isEmpty()){
        if(subcommand){
            result += "{";
        }
        foreach(GIftCommand * c, subcommands ){
            result += c->toString(true) + " ";
        }
        if(subcommand){
            result += "}";
        }
    }
    if(!subcommand){
        result += ";";
    }
    return result;
}
