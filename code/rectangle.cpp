#include "rectangle.h"

Rectangle::Rectangle(QWidget *parent) : QWidget(parent)
{
    //qDebug()<<"rectangle";
}
Rectangle::Rectangle(int x,int y,int w,int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    /*leftmargin = 20;
    rightmargin = 980;
    topmargin = 20;
    bottommargin = 980;
    */
    //setFixedSize(w,h);

    //setFocus(Qt::ActiveWindowFocusReason);
    //setSizePolicy(QSizePolicy::Fixed);
}
void Rectangle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawRect(0,0,100,100);
/*
   QPainter painter(this);
   painter.setBrush(Qt::white);
   painter.setPen(Qt::SolidLine);
   painter.drawRect(x,y,w,h);*/
}
/*
void Rectangle::paintEvent(QPaintEvent *)
{
    qDebug()<<"paintEvent_rectangle";
    bool drawHelpGrid = true;
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::SolidLine);
    painter.drawRect(x,y,w,h);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::SolidLine);
    for(int i = 0; i<59; i++)
    {

        if(i == 11 || i == 23 || i == 35 || i == 47 || i == 59)
            continue;
        painter.drawLine(leftmargin,topmargin+i*20,rightmargin,topmargin+i*20);

    }

if(drawHelpGrid)
    for(int i = leftmargin; i<=rightmargin; i+=10)
        painter.drawLine(i,topmargin,i,bottommargin);
}
*/


