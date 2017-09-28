#include "cursor.h"
//#include <QRect>
#include <QDebug>
Cursor::Cursor(int x, int y, int w, int h)
{
    QPoint point(x,y);
    QSize size(w,h);
    QSize symbolsize(w/2,h/2);
    //QRect rect(x,y,w,h);
    setTopLeft(point);
    setSize(size);
    //qDebug()<<"Hei på deg";
    mini=false;
    //QRect(x,y,w,h);
    //this->point.setX(x);
    //this->point.setY(y);
    //this->size.setWidth(w);
    //this->size.setHeight(h);
    //setTopLeft(point);
    //setSize(size);
    ct = cfree;

    //qDebug()<<"cursor"<<&point<<x<<y<<w<<h;
}
void Cursor::setTopCursor()
{
    translate(0,-QRect::height()/2);
    cursorOption=1;
}

void Cursor::setPostCursor()
{
    translate(QRect::width()/2,QRect::height()/4);
    cursorOption=2;
}

void Cursor::setNormalCursor()
{
    translate(-QRect::width()/2,QRect::height()/4);
    cursorOption=0;
}
void Cursor::setSymbolCursor()
{
    //size.scale(w/2,h/2,Qt::IgnoreAspectRatio);
    //setSize(size);
    //setWidth(w/2);
    //setHeight(h/2);
}
bool Cursor::isMini()
{
    return mini;
}
void Cursor::setMini(bool m)
{
    mini=m;
}
bool Cursor::isTop()
{
    return top;
}
void Cursor::setTop(bool t)
{
    top=t;
}
void Cursor::moveCursorUp()
{
    //setTop(true);
    //translate(0,-QRect::height()*1.5);
    translate(0,-VSTEP);
    qDebug()<<"cursor up";
}
void Cursor::moveCursorDown()
{
    //setTop(false);
    //translate(0,QRect::height()*1.5);
    translate(0,VSTEP);
    qDebug()<<"Down "<<QRect::height()*1.5;
}
void Cursor::moveCursorLeft()
{
    if(intersecting)
       translate(-QRect::width()*10,0);
    else
        translate(-QRect::width()*1,0);
}

void Cursor::moveCursorRight()
{
    if(intersecting)
        translate(QRect::width()*10,0);
    else
        translate(QRect::width()*1,0);
}
void Cursor::moveCursorGapUp()
{
    //setTop(false);
    //translate(0,-(QRect::height()+HOR_SPACE));
    translate(0,-VSTEP);
    qDebug()<<"cursor gap up";
}
void Cursor::moveCursorGapDown()
{
    //setTop(true);
    //translate(0,QRect::height()*2+HOR_SPACE);
    translate(0,VSTEP);
   //  qDebug()<<"Gap "<<QRect::height()+HOR_SPACE;
}
void Cursor::moveCursorTabLeft()
{
    translate(-QRect::width()*10,0);
}
void Cursor::moveCursorTabRight()
{
    translate(QRect::width()*10,0);
}
QPoint Cursor::getPoint()
{
    return topLeft();
}
QPoint Cursor::getTopToNormalPoint()
{
    QPoint tmp(QRect::topLeft().x(),QRect::topLeft().y()+QRect::height()*1.5);
    return tmp;
}
void Cursor::setIntersecting(bool value)
{
    intersecting = true;
}
bool Cursor::isIntersecting()
{
    return intersecting;
}
bool Cursor::isBigBox()
{
    return bigBox;
}
void Cursor::setBigBox(bool value)
{
    bigBox = value;
}
