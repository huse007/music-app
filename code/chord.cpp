#include "chord.h"

Chord::Chord(QObject *parent) : QObject(parent)
{

}
Chord::Chord(QString number,QPoint point)
{
    this->number = number;
    this->point = point;
    diamond = false;
    hat = "";
    tail = "";
    hatPoint = point;
    hatPoint.setY(hatPoint.y()+CURSOR_HEIGHT);
    qDebug()<<"Chord::point: "<<point.y();
    qDebug()<<"Chord::hatpoint: "<<hatPoint.y();
}
QPoint Chord::getPoint()
{
    return point;
}

QString Chord::getNumber()
{
    return number;
}
QString Chord::getHat()
{
    return hat;
}
QString Chord::getTail()
{
    return tail;
}
QString Chord::getFront()
{
    return front;
}

void Chord::setNumber(QString number)
{
    this->number = number;
}
void Chord::setHat(QString hat)
{
    this->hat = hat;
}
void Chord::setTail(QString tail)
{
    this->tail = tail;
}
void Chord::setFront(QString front)
{
    this->front = front;
}

void Chord::setDiamond(bool status)
{
    diamond = status;
}

bool Chord::isDiamond()
{
    return diamond;
}
void Chord::addTopSymbol(QString symbol)
{
    top_vec.push_back(symbol);
}
QVector<QString> Chord::getTopSymbol()
{
    return top_vec;
}
