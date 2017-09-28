#include "symbol.h"

Symbol::Symbol(QObject *parent) : QObject(parent)
{

}
QPixmap get4note()
{
    return new QPixmap("/qt_notes/8.png");
}
