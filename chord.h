#ifndef CHORD_H
#define CHORD_H

#include <QObject>
#include <QChar>
#include <QPoint>
#include <QString>
#include <QDebug>
#include <global.h>
class Chord : public QObject
{
    Q_OBJECT
private:
    QString number;
    QString hat;
    QString tail;
    QString front;
    bool diamond;
    QPoint point;
    QPoint hatPoint;
    QVector<QString> top_vec;

public:
    explicit Chord(QObject *parent = 0);
    Chord(QString number,QPoint point);

    QPoint getPoint();
    QPoint getHatPoint();
    QString getNumber();
    QString getHat();
    QString getTail();
    QString getFront();
    QVector<QString> getTopSymbol();
    void setNumber(QString number);
    void setHat(QString hat);
    void setTail(QString tail);
    void setDiamond(bool status);
    void setFront(QString front);
    bool isDiamond();
    void addTopSymbol(QString symbol);

signals:

public slots:
};

#endif // CHORD_H
