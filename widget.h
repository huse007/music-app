#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <rectangle.h>
#include <QKeyEvent>
#include <QGridLayout>
#include <QRect>
#include <QScrollArea>
#include <title.h>
#include <logo.h>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QMenu>
#include <vector>
#include <cursor.h>
#include <page.h>

#include <QPlainTextEdit>

const int MAX_PAGE = 10;
class Widget : public QWidget
{
    Q_OBJECT
private:
    Cursor *cursor;
    int xwindow,ywindow;
    int stretch,index;
    QVBoxLayout *qvbl,*page_layout;
    QHBoxLayout *qhbl;
    QScrollArea *s,*scrollArea;
    QPalette *pal;
    Page *p;
    Cursor *c;

    QPlainTextEdit *textEdit;

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    std::vector<Page*> page;
    Title *t;
    Logo *l;
    Rectangle *scene;
    void keyPressEvent(QKeyEvent *event);
    QGridLayout *layout;
    void paintEvent(QPaintEvent *);
    QGroupBox* createPushButtonGroup();
    void addPage();
public slots:
    void handleButtonNew();
    void handleButtonOpen();
    void handleButtonSave();
    void handleButtonQuit();
    void handleButtonDoc();
    void handleButtonKey();
    void handleButtonTime();
    void handleButtonExport();
    void handleButtonLegato();

};

#endif // WIDGET_H
