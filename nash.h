#ifndef NASH_H
#define NASH_H

#include <nashville.h>

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QPainter>
#include <QDebug>
#include <cursor.h>
#include <QKeyEvent>
#include <note.h>
#include <QDialogButtonBox>
#include <QDialog>
#include <QInputDialog>
#include <QDir>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPrinter>
#include <QMessageBox>
#include <chord.h>
#include <global.h>
#include <symboldialog.h>
#include <line.h>
#include <QTableView>
#include <QTextBoundaryFinder>
//#include <QtSqlTableModel>
#include <QStandardItemModel>
#include <element.h>
#include <QSvgWidget>
#include <QSvgRenderer>
#include <QGroupBox>
//still CURSOR_HEIGTH i global og skift så mange referanser som mulig
#define global_cursorsize 15
#define global_minicursorsize 10
#define MARGIN_LEFT 20
#define MARGIN_RIGHT 20
#define MARGIN_TOP 120
#define MARGIN_BOTTOM 20
#define INDENT_HEADER 10
#define INDENT_CURSOR 120
#define PART_SIZE global_cursorsize*1.5
#define TOP_SIZE global_cursorsize*1.5
#define MARGINSYMBOL_SIZE global_cursorsize*2
#define BIGSYMBOL_SIZE global_cursorsize
#define POST_SIZE global_cursorsize
#define X_PRINT_CORR 20
#define Y_PRINT_CORR 50
#define HOR_SPACE 20
//#define CHORD_SIZE
//#define SYMBOL_SIZE
class Nashville;
//class Nash : public QWidget
class Nash : public Nashville
{
    Q_OBJECT

private:
    int leftmargin,rightmargin,topmargin,bottommargin;
    int x,y,w,h;
    QScrollArea *scrollArea;
    int cursorWidth, cursorHeight,minicursorWidth,minicursorHeight,bigcursorHeigth,bigcursorWidth;
    QString artist,song,key,time;
    QVector<int> neckPosition;
    Cursor *c;
    int lastLine;
    QVector<Note*> n;
    QVector<Note*> top;
    QVector<Note*> bigSymbol;
    QVector<Note*> post;
    QVector<Note*> min;
    QVector<Note*> minor;
    QVector<QRect*> rect;
    QVector<QPoint> diam;
    QVector<Note*> txt;
    QVector<Note*> part;
    QVector<Note*> chord;
    QVector<Chord*> ch;
    QVector<Element*> element;
    QDialogButtonBox *settings;
    QVector<QPoint> lines;
    QVector<Line*> line_vec;

    void makeMiniCursor();
    void makeBigCursor();
    void makePostCursor();
    //void makeMinorCursor();
public:
    explicit Nash(Nashville *parent = 0);
    Nash(int x,int y, int w, int h, QScrollArea *scrollArea);
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *event);
    Note* clearNote(QPoint point);

    Note* clearTop(QPoint point);
    Note* clearChord(QPoint point);
    Note* clearPart(QPoint point);
    void insertSymbol(QChar text,QPoint point);
    void insertBigSymbol(QChar text,QPoint point); //symbols that don't fit in the cursor
    void insertTop(QString text,QPoint point);
    void insertPost(QChar text,QPoint point);
    void insertMinor(QChar text,QPoint point);
    void insertText(QString text,QPoint point);
    void insertPart(QString text,QPoint point);
    void insertChord(QString text,QPoint point);
    void toggleDiamond(bool status);
    void insertPreSymbol(QString text);

    int getWidth();
    void insertNumber(QChar text,QPoint point);
    void insertTail(QString txt,QPoint point);
    void insertCenterSymbol(QString txt,QPoint point);
    Chord* deleteChord(QPoint point);

    void toggleCursor();
    void toggleCursorPost();
    //void getSettings();
    void exportPDF();
    void moveCursorToTop();
    void moveCursorDown();
    Chord* getChord(QPoint p);
    QVector<QPoint> getLines();
    bool isInLines(QPoint p);
    int getLineFromCursor(QPoint p);
    bool isPointBusy(QPoint point);
    bool comparePoints(QPoint p1,QPoint p2);
    bool clearPoint(QPoint point);
    int warningRemoveSymbol();
    //void showSymbolDialog();

    //void handleButton(QString group,QString symbol);

signals:

public slots:
//    void handleButton(QString group,QString symbol);
    void handlePart(QString symbol);
    void handleSymbol(QString symbol);
    void handleChord(QString chord);
    void handleDocument(QString document);
    void handleLeftSymbol(QString symbol);
    void handleRightSymbol(QString symbol);
    void handlePreSymbol(QString symbol);
    void handleCenterSymbol(QString symbol);
    void showSymbolDialog();
    void showAbout();
    void showWhatIs();
    void getSettings();
};

#endif // NASH_H
