#include "slide.h"

Slide::Slide(QWidget *parent) : QWidget(parent)
{

}

Slide::Slide(QPoint p1)
{
    this->p1 = p1;
    complete = false;
}
bool Slide::isComplete()
{
    return complete;
}
void Slide::setComplete(bool complete)
{
    this->complete = complete;
}
void Slide::setSecondPoint(QPoint p2)
{
    this->p2 = p2;
    setComplete(true);
}
QPoint Slide::getFirst()
{
    return p1;
}
QPoint Slide::getSecond()
{
    return p2;
}
int Slide::getX()
{
    return p1.x();
}
int Slide::getY()
{
    return p1.y();
}
int Slide::getW()
{
    return p2.x()-p1.x();
}
int Slide::getH()
{
    return 10;
}

