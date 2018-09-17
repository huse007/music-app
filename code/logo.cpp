#include "logo.h"

Logo::Logo(QWidget *parent) : QWidget(parent)
{

}
Logo::Logo(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    setFixedSize(w,h);
}


void Logo::paintEvent(QPaintEvent *)
{
    //qDebug()<<"Logo->paintEvent()";
    QImage image("ps5_logo3.png");
    image = image.scaled(200,200);
    //image.
    QColormap colormap=QColormap::instance();

    //image.fill(colormap.pixel(Qt::green));
    QPainter painter(this);//endret
    painter.drawImage(0,0,image);
    //qDebug()<<"Logo->paintEvent finished";
}
