#ifndef NASHVILLE_H
#define NASHVILLE_H

#include <QObject>
#include <QWidget>
#include <title.h>
#include <logo.h>
#include <nash.h>

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSignalMapper>
#include <QMenuBar>
//#include <QMainWindow>
#include <QToolBar>
#include <QGridLayout>
#include <QApplication>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGTH 2000
#define UNICODE_FLAT 0x266d
#define UNICODE_SHARP 0x266f
#define BUTTON_W 100
class Nash;
class Nashville : public QWidget
{
    Q_OBJECT
private:
    QScrollArea *s,*scrollArea;
    QVBoxLayout *qvbl,*qvbl2,*page_layout;
    QHBoxLayout *qhbl,*qhbl2;
    Nash *n;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *file,*edit,*insert,*help,*part;
    QAction *newdoc,*open,*save,*saveas,*quit,*symbols,*about,*whatis;
    QAction *intro,*verse,*chorus,*channel,*tag,*turnaround,*bridge,*mid8,*solo,*outro;
    QAction *artist,*song,*key,*time;


public:
    explicit Nashville(QWidget *parent = 0);
    Title *t;
    Logo *l;
    QGroupBox* createPushButtonGroup();
    QGroupBox* createPartButtonGroup();
    QGroupBox* createChordButtonGroup();
    QGroupBox* createTriadButtonGroup();
    QGroupBox* createDocumentButtonGroup();
    QGroupBox* create7ButtonGroup();
    QGroupBox* create9ButtonGroup();
    QGroupBox* createSymbolButtonGroup();
    QGridLayout *layout;
    QString convertUnicodeToString(uint32_t symbol);
    QGroupBox *b1;

signals:

public slots:
    //void handleButton(QString group,QString symbol);
};

#endif // NASHVILLE_H
