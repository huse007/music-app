#ifndef LEGATO_H
#define LEGATO_H

#include <QWidget>

class Legato : public QWidget
{
    Q_OBJECT
private:
    bool complete;
    QPoint p1;
    QPoint p2;
    int startAngle, spanAngle;
public:
    explicit Legato(QWidget *parent = 0);
    Legato(QPoint p1);
    bool isComplete();
    void setComplete(bool complete);
    void setSecondPoint(QPoint p2);
    QPoint getFirst();
    QPoint getSecond();
    int getX();
    int getY();
    int getW();
    int getH();
    int getStartAngle();
    int getSpanAngle();
signals:

public slots:
};

#endif // LEGATO_H
