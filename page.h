#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
//#include <rectangle.h>
#include "config.h"
#include <QScrollArea>
#include <QDebug>
#include <QPainter>
#include <cursor.h>
#include <QKeyEvent>
#include <QVector>
#include <note.h>
#include <QScrollBar>
#include <QFont>
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QtMath>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QPdfWriter>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QPushButton>
#include <QCoreApplication>
#include <iterator>
#include <legato.h>
#include <slide.h>
extern QString dtype;
class Page : public QWidget
{
private:
    int leftmargin,rightmargin,topmargin,bottommargin;
    int x,y,w,h;
    int scrollPos;
    int stringNumber,lastLine;
    int cursorWidth, cursorHeight,global_cursorsize;
    QString artist,song,key,time;
    QVector<int> neckPosition;
    QVector<QVector<Note*>> grid;
    Cursor *c;
    QVector<Note*> n;
    QScrollArea *scrollArea;
    QScrollBar *bar;
    QFile *file;
    QVector<Legato*> leg;
    QVector<Slide*> slideup,slidedown;
public:
    bool doExport;
    QString fileName;
    QPdfWriter *writer;
    QPainter *p;


public:
    Page();
    Page(int x,int y, int w, int h, QScrollArea *scrollArea);

    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *event);
    void print_init();
    void drawCursor();
    void drawSymbol();
    void insertSymbol(QChar text,QPoint point);
    Note* clearNote(QPoint point);
    void addTabs();
    void setTitle();
    void setKey();
    void save();
    void setTime();
    void doScroll();
    void exportPDF();
    void quit();
    void open();
    void newProject();
    bool legato();
    QVector<QVector<Note *> > generateGrid();
public slots:
    void test();
};

#endif // PAGE_H
