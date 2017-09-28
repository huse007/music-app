#ifndef LINE_H
#define LINE_H
#include "global.h"
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QDebug>
class Line : public QWidget
{
private:
    QPoint tleft;
    //QVector<*Note> note_list;
    QString part;
    QString lsymbol;
    QString rsymbol;


public:
    Line();
    Line(QString p,int y_pos);
    virtual void paintEvent(QPaintEvent *);
    QString getPart();
    void setPart(QString text);
    QPoint getPoint();
    void setLSymbol(QString text);
    void setRSymbol(QString text);
    QString getLSymbol();
    QString getRSymbol();

};

#endif // LINE_H
