#include "config.h"

Config::Config(QObject *parent) : QObject(parent)
{

}
Config::setDocument(QString s)
{
    documentType=s;
}
Config::setGuitar(QString s)
{
    guitarType=s;
}

Config::setStringNumber(int i)
{
    stringType=i;
}
Config::getDocument()
{
    return documentType;
}
Config::getGuitar()
{
    return guitarType;
}
Config::getStringNumber()
{
    return stringType;
}
