#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QPoint>
class Element : public QObject
{
    Q_OBJECT
private:
    QString element;
    QPoint point;
public:
    explicit Element(QObject *parent = 0);
    Element(QString element,QPoint point);
    QPoint getPoint();
    QString getElement();
    void setPoint(QPoint point);
    void setElement(QString element);
signals:

public slots:
};

#endif // ELEMENT_H
