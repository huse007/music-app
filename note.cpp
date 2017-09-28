#include "note.h"
Note::Note(QString txt,QPoint point)
{
    this->txt = txt;
    this->point=point;
}

Note::Note(QChar symbol,QPoint point)
{
this->symbol = symbol;
this->point = point;
}
Note::Note()
{
symbol = '\0';
}

QPoint Note::getPoint() const
{
    return point;
}

QChar Note::getSymbol() const
{
    return symbol;
}
QString Note::getText() const
{
    return txt;
}
void Note::setText(QString text)
{
    txt = text;
}

Note* Note::copy() const
{
    return NULL;
}
