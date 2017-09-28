#include "line.h"

Line::Line()
{

}
Line::Line(QString p,int y_pos)
{
    part = p;
    tleft.setY(y_pos);
    tleft.setX(0);

}

void Line::paintEvent(QPaintEvent *)
{
    qDebug()<<"LINE PAINT";
    QPainter painter(this);
    QFont fname("Ume P Gothic C4",20);
    QFont fname2("Helvetica [Cronyx]",20);

    painter.setFont(fname);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::SolidLine);
    painter.drawText(400,400,part);

}
QString Line::getPart()
{
    return part;
}
QPoint Line::getPoint()
{
    return tleft;
}
void Line::setPart(QString text)
{
    part = text;
}
void Line::setLSymbol(QString text)
{
    lsymbol = text;
}
void Line::setRSymbol(QString text)
{
    rsymbol = text;
}

QString Line::getLSymbol()
{
    return lsymbol;
}
QString Line::getRSymbol()
{
    return rsymbol;
}
