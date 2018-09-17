#ifndef LOGO_H
#define LOGO_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QColormap>

class Logo : public QWidget
{
    Q_OBJECT
private:
    int x,y,w,h;
public:
    explicit Logo(QWidget *parent = 0);
    Logo(int x,int y,int w,int h);

    virtual void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // LOGO_H
