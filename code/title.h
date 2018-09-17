#ifndef TITLE_H
#define TITLE_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

#define TITLE_WIDTH 550
#define TITLE_HEIGTH 100
class Title : public QWidget
{
    Q_OBJECT
private:
    int x,y,w,h;
    QString header;
public:
    explicit Title(QWidget *parent = 0);
    Title(int x,int y,int w,int h,QString header);
    //void setInfo();
    virtual void paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // TITLE_H
