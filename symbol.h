#ifndef SYMBOL_H
#define SYMBOL_H

#include <QObject>
#include <QPixmap>
class Symbol : public QObject
{
    Q_OBJECT
private:
    QString path = "qt_notes/";
public:
    explicit Symbol(QObject *parent = 0);
    QPixmap get4note();

signals:

public slots:
};

#endif // SYMBOL_H
