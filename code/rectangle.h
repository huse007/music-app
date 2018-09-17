#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
class Rectangle : public QWidget
{
    Q_OBJECT
//private:
protected:
    int x,y,w,h;
    //int leftmargin,rightmargin,topmargin,bottommargin;
public:
    explicit Rectangle(QWidget *parent = 0);
    Rectangle(int x,int y, int w, int h);
virtual void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // RECTANGLE_H
