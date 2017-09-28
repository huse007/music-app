#ifndef CURSOR_H
#define CURSOR_H
#include <QRect>
#include <QPaintDevice>
#include <QWidget>
#include <global.h>
#define HOR_SPACE 30
//#define global_cursorsize 15
#define VSTEP 105
class Cursor : public QRect,public QWidget
{

private:
    int x,y,w,h;
    QPoint point;
    QSize size;
    QSize symbolsize;
    int cursorOption;
    bool mini;
    bool top;
    bool intersecting;
    bool bigBox;



public:
    Cursor(int x, int y, int w, int h);
    enum CursorType {cfree,cbox,cnumber,ctop,ctail};
    CursorType ct;
    //void setCursorSize(int x, int y, int w, int h);
    void setTopCursor();
    void setPostCursor();
    void setNormalCursor();
    void getCursorOption();
    void setSymbolCursor();
    bool isMini();
    void setMini(bool);
    bool isTop();
    void setTop(bool);
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorUp();
    void moveCursorDown();
    void moveCursorGapUp();
    void moveCursorGapDown();
    void moveCursorTabLeft();
    void moveCursorTabRight();
    QPoint getPoint();
    QPoint getTopToNormalPoint();
    bool isIntersecting();
    void setIntersecting(bool value);
    bool isBigBox();
    void setBigBox(bool value);

};

#endif // CURSOR_H
