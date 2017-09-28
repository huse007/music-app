#include "title.h"

Title::Title(QWidget *parent) : QWidget(parent)
{

}
Title::Title(int x, int y, int w, int h,QString header)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->header = header;
    setFixedSize(w,h);
}

void Title::paintEvent(QPaintEvent *)
{
    //qDebug()<<"Title->paintEvent";
    QPainter painter(this);
    QFont fname("Ume P Gothic C4",30);
    QFont fname2("Helvetica [Cronyx]",15);
    //QString pname("Pedal Steel Guitar Tabs");

    QString author("by Anders Huse Pedersen");
    QFontMetrics fm(fname);

    painter.setBrush(Qt::white);
    painter.setPen(Qt::SolidLine);
    fname.setBold(true);
    int width = fm.width(header);
    painter.setBrush(Qt::blue);
    painter.setFont(fname);
    painter.drawText(w/2-width/2,y+40,header);
    fname.setPointSize(10);
    painter.setFont(fname2);
    painter.drawText(w/2,y+60,author);
}
