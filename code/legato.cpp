#include "legato.h"

Legato::Legato(QWidget *parent) : QWidget(parent)
{

}
Legato::Legato(QPoint p1)
{
    this->p1 = p1;
    complete = false;
}
bool Legato::isComplete()
{
    return complete;
}
void Legato::setComplete(bool complete)
{
    this->complete = complete;
}
void Legato::setSecondPoint(QPoint p2)
{
    this->p2 = p2;
    setComplete(true);
}
QPoint Legato::getFirst()
{
    return p1;
}
QPoint Legato::getSecond()
{
    return p2;
}
int Legato::getX()
{
    return p1.x();
}
int Legato::getY()
{
    return p1.y();
}
int Legato::getW()
{
    return p2.x()-p1.x();
}
int Legato::getH()
{
    return 10;
}
int Legato::getSpanAngle()
{
    return 180*16;
    //return 5760/2;
}
int Legato::getStartAngle()
{
    return 0*16;//30*16;
}
