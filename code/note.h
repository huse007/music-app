#ifndef NOTE_H
#define NOTE_H

#include <QChar>
#include <QPoint>
#include <QString>
class Note
{
private:
    QString txt;
    QChar symbol;
    QPoint point;
    //QPoint getPoint();

public:
    Note();
    Note(QChar symbol,QPoint point);
    Note(QString txt,QPoint point);
    QChar getSymbol() const;
    QPoint getPoint() const;
    Note* copy() const;
    QString getText() const;
    void setText(QString text);

};

#endif // NOTE_H

//a->getPoint()
//a->getPoint().x()
