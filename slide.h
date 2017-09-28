#ifndef SLIDE_H
#define SLIDE_H

#include <QWidget>

class Slide : public QWidget
{
    Q_OBJECT
private:
    bool complete;
    QPoint p1;
    QPoint p2;
    int startAngle;
public:
    explicit Slide(QWidget *parent = 0);
    Slide(QPoint p1);
    bool isComplete();
    void setComplete(bool complete);
    void setSecondPoint(QPoint p2);
    QPoint getFirst();
    QPoint getSecond();
    int getX();
    int getY();
    int getW();
    int getH();


signals:

public slots:
};

#endif // SLIDE_H
