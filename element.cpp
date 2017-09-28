#include "element.h"

Element::Element(QObject *parent) : QObject(parent)
{

}
Element::Element(QString element, QPoint point)
{
    this->element = element;
    this->point = point;
}
QString Element::getElement()
{
    return element;
}
QPoint Element::getPoint()
{
    return point;
}
void Element::setElement(QString element)
{
    this->element = element;
}
void Element::setPoint(QPoint point)
{
    this->point = point;
}
