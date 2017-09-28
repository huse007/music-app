#include "nashville.h"

Nashville::Nashville(QWidget *parent) : QWidget(parent)
{


    setWindowTitle("Nashville Number System"
                   "");
    QPalette pal;
    t = new Title(0,20,TITLE_WIDTH*1.8,TITLE_HEIGTH,"Nashville Number Editor");
    scrollArea = new QScrollArea();

    b1 = createSymbolButtonGroup();
    qDebug()<<"3";
    n = new Nash(0,0,WINDOW_WIDTH,WINDOW_HEIGTH,scrollArea);//////////////////////////////////////////////////////
    qvbl = new QVBoxLayout();
    qvbl2 = new QVBoxLayout();
    qhbl = new QHBoxLayout();
    qhbl2 = new QHBoxLayout();
    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidget(n); /////////////////////////////////////////////////////////////////////////////////////7
    scrollArea->setAlignment(Qt::AlignCenter);
    qApp->setStyleSheet("QPushButton {font-family:\"lastresort\";}");
    //background-color: yellow;

    qvbl2->addWidget(t,0);
    qvbl2->addLayout(qhbl);

    qvbl->addWidget(createDocumentButtonGroup());
    qvbl->addWidget(createPartButtonGroup());
    qvbl->addWidget(createTriadButtonGroup());
    qvbl->addWidget(create9ButtonGroup());
    //qvbl->addWidget(createSymbolButtonGroup());
    qvbl->addWidget(b1);
    qvbl->setAlignment(Qt::AlignTop);
    qhbl->addLayout(qvbl);
    qhbl->addWidget(scrollArea,0);
    menuBar = new QMenuBar();
    qhbl->addWidget(menuBar);

    /* menubar */
    file = menuBar->addMenu("File");
    edit = menuBar->addMenu("Edit");
    insert = menuBar->addMenu("Insert");
    help = menuBar->addMenu("Help");

    /* file actions */
    newdoc = new QAction("New");
    open = new QAction("Open");
    save = new QAction("Save");
    saveas = new QAction("Save As");
    quit = new QAction("Quit");
    file->addAction(newdoc);
    file->addAction(open);
    file->addAction(save);
    file->addAction(saveas);
    file->addAction(quit);

    /* insert actions */
    part = new QMenu("Part");
    insert->addMenu(part);
    QStringList parts,shortcuts;
    parts <<"Intro"<<"Verse"<<"Chorus"<<"Channel"<<"Tag"<<"Bridge"<<"TA"<<"Mid-8"<<"Solo"<<"Outro";
    shortcuts <<"Alt+I"<<"Alt+V"<<"Alt+C"<<"Alt+H"<<"Alt+G"<<"Alt+B"<<"Alt+T"<<"Alt+M"<<"Alt+S"<<"Alt+O";
    QVector<QAction*> action;
    QSignalMapper *mapper = new QSignalMapper(this);

    for(int i = 0; i<parts.size(); i++)
    {
        action.push_back(new QAction(parts.at(i)));
        part->addAction(action.at(i));
        action.at(i)->setShortcut(shortcuts.at(i));
        connect(action.at(i),SIGNAL(triggered()),mapper,SLOT(map()));
        mapper->setMapping(action.at(i),action.at(i)->text());

    }

    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handlePart(QString))); //ENDRET fra n til this

    symbols = new QAction("View Symbols");
    artist = new QAction("Artist");
    song = new QAction("Song");
    key = new QAction("Key");
    time = new QAction("Time");
    /*intro = new QAction("Intro");
    verse = new QAction("Verse");
    chorus = new QAction("Chorus");
    channel = new QAction("Channel");
    tag = new QAction("Tag");
    bridge = new QAction("Bridge");
    turnaround = new QAction("Turn Around");
    mid8 = new QAction("Mid-8");
    solo = new QAction("Solo");
    outro = new QAction("Outro");*/

    /*part->addAction(intro);
    part->addAction(verse);
    part->addAction(chorus);
    part->addAction(channel);
    part->addAction(tag);
    part->addAction(bridge);
    part->addAction(turnaround);
    part->addAction(mid8);
    part->addAction(solo);
    part->addAction(outro);*/

    insert->addAction(symbols);
    insert->addAction(artist);
    insert->addAction(song);
    insert->addAction(key);
    insert->addAction(time);

    /* help actions */
    whatis = new QAction("What is Nashville Numbering System?");
    about = new QAction("About");
    help->addAction(whatis);
    help->addAction(about);

    /* short cuts */

    open->setShortcut(QKeySequence("Ctrl+O"));
    save->setShortcut(QKeySequence("Ctrl+S"));
    saveas->setShortcut(QKeySequence("Ctrl+W"));
    quit->setShortcut(QKeySequence("Ctrl+Q"));
    symbols->setShortcut(QKeySequence("Ctrl+U"));
    /*intro->setShortcut(QKeySequence("Alt+I"));
    verse->setShortcut(QKeySequence("Alt+V"));
    chorus->setShortcut(QKeySequence("Alt+C"));
    channel->setShortcut(QKeySequence("Alt+H"));
    tag->setShortcut(QKeySequence("Alt+G"));
    bridge->setShortcut(QKeySequence("Alt+B"));
    turnaround->setShortcut(QKeySequence("Alt+T"));
    mid8->setShortcut(QKeySequence("Alt+M"));
    solo->setShortcut(QKeySequence("Alt+S"));
    outro->setShortcut(QKeySequence("Alt+O"));
*/
    /* signals/slots */
   // QSignalMapper *mapper = new QSignalMapper(this);
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(symbols,SIGNAL(triggered()),n,SLOT(showSymbolDialog())); //ENDRET FRA n til this
    connect(about,SIGNAL(triggered()),n,SLOT(showAbout()));
    connect(whatis,SIGNAL(triggered()),n,SLOT(showWhatIs()));
    connect(artist,SIGNAL(triggered()),n,SLOT(getSettings()));
  /*  connect(intro,SIGNAL(triggered()),mapper,SLOT(map()));
    connect(verse,SIGNAL(triggered()),mapper,SLOT(map()));
    mapper->setMapping(intro,intro->text());
    mapper->setMapping(verse,verse->text());
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handlePart(QString)));*/
    setLayout(qvbl2);
}
QGroupBox *Nashville::createDocumentButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Document"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList document;
    document <<"New"<<"Open"<<"Save"<<"Settings"<<"Quit"<<"Export";
    QVector<QPushButton*> b;
    for(int i = 0; i<document.size(); i++){
        b.push_back(new QPushButton(document[i]));
        //b[i]->setMaximumWidth(BUTTON_W);
        b[i]->setFocusPolicy(Qt::NoFocus);
        gbox->addWidget(b[i],i/3,i%3);

        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],document[i]);
   }
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handleDocument(QString))); //Endret fra n til this
   // gbox->setVerticalSpacing(0);
   // gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(100);
    groupBox->setLayout(gbox);
    return groupBox;
}

//Grid Layout
QGroupBox *Nashville::createTriadButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Triad"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList chord;
    chord <<"min"<<"maj"<<"sus2"<<"sus4"<<"dim"<<"aug";
    QVector<QPushButton*> b;
    for(int i = 0; i<chord.size(); i++){
        b.push_back(new QPushButton(chord[i]));
        //b[i]->setMaximumWidth(BUTTON_W);
        b[i]->setFocusPolicy(Qt::NoFocus);
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],chord[i]);
   }
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handleChord(QString))); //Endret fra n til this
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(100);
    groupBox->setLayout(gbox);
    return groupBox;
}
QGroupBox *Nashville::createPartButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Part"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList part;
    part<<"Intro"<<"Verse"<<"Chorus"<<"TA"<<"Tag"<<"Channel"<<"Mid-8"<<"Solo"<<"Outro";
    QVector<QPushButton*> b;
    for(int i = 0; i<part.size();i++)
    {
         b.push_back(new QPushButton(part[i]));
         //b[i]->setMaximumWidth(BUTTON_W);
         b[i]->setFocusPolicy(Qt::NoFocus);
         gbox->addWidget(b[i],i/3,i%3);
         connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
         mapper->setMapping(b[i],part[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),this,SLOT(handlePart(QString))); //Endret fra n til this
    //hbox->addStretch(1);
    //vbox->addLayout(hbox);
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(150);
    groupBox->setLayout(gbox);
    return groupBox;
}
QGroupBox *Nashville::createSymbolButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Symbol"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList symbol;
    //QString triangle = QChar(0x25b2);
    //QString triangleR = QChar(0x25b6);
    QString circle = QChar(0x25cf);
    QString flat = QChar(UNICODE_FLAT);
    QString sharp = QChar(UNICODE_SHARP);
    QString repeatl = convertUnicodeToString(0x1d106);
    QString repeatr = convertUnicodeToString(0x1d107);
    QString note4 = QChar(0x2669);
    QString note8 = QChar(0x266a);
    QString note16 = QChar(0x1d161);
    QString pause = convertUnicodeToString(0x1d13D);
    QString triangle = convertUnicodeToString(0x1D149);
    symbol <<"<"<<"<<"<<"^"<<triangle<<pause<<note16<<flat<<sharp<<repeatl<<repeatr<<note4<<note8;
    QVector<QPushButton*> b;
    //QFont f("arial");
    //f.setBold(true);
    for(int i = 0; i<symbol.size(); i++){
        b.push_back(new QPushButton(symbol[i]));
       // b[i]->setMaximumWidth(BUTTON_W);
        b[i]->setFocusPolicy(Qt::NoFocus);
        //b[i]->setFont(f);
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],symbol[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handleSymbol(QString)));
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(200);
    groupBox->setLayout(gbox);
    return groupBox;
}
QGroupBox* Nashville::createPushButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("MENU"));
    groupBox->setChecked(true);
    QPushButton *button1 = new QPushButton(tr("&New"));
    button1->setFocusPolicy(Qt::NoFocus);
    QHBoxLayout *hbox1 = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    hbox1->addWidget(button1);
    hbox1->addStretch(1);
    vbox->addLayout(hbox1);
    groupBox->setLayout(vbox);
    return groupBox;
}
/*
 * QGroupBox *Nashville::createPartButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Part"));
    groupBox->setChecked(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    QStringList part;
    part<<"Intro"<<"Verse"<<"Chorus"<<"TA"<<"Tag"<<"Channel"<<"Mid-8"<<"Solo"<<"Outro";
    QVector<QPushButton*> b;
    for(int i = 0; i<part.size();i++)
    {
         b.push_back(new QPushButton(part[i]));
         b[i]->setFocusPolicy(Qt::NoFocus);
         hbox->addWidget(b[i]);
         connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
         mapper->setMapping(b[i],part[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handlePart(QString)));
    hbox->addStretch(1);
    vbox->addLayout(hbox);
    groupBox->setLayout(vbox);
    return groupBox;
}
*/
QGroupBox *Nashville::createChordButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Chord"));
    groupBox->setChecked(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    QStringList chord;
    chord <<"Custom";
    QVector<QPushButton*> b;
    for(int i = 0; i<chord.size(); i++){
        b.push_back(new QPushButton(chord[i]));
        b[i]->setFocusPolicy(Qt::NoFocus);
        hbox->addWidget(b[i]);
    }
    hbox->addStretch(1);
    vbox->addLayout(hbox);
    groupBox->setLayout(vbox);
    return groupBox;
}


/*** Not Grid Layout
  QGroupBox *Nashville::createTriadButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Triad"));
    groupBox->setChecked(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;    
    QStringList chord;
    chord <<"min"<<"maj"<<"sus2"<<"sus4"<<"dim"<<"aug";
    QVector<QPushButton*> b;
    for(int i = 0; i<chord.size(); i++){
        b.push_back(new QPushButton(chord[i]));
        b[i]->setFocusPolicy(Qt::NoFocus);
        hbox->addWidget(b[i]);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],chord[i]);
   }
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handleChord(QString)));
    hbox->addStretch(1);
    vbox->addLayout(hbox);
    groupBox->setLayout(vbox);
    return groupBox;
}*/

QGroupBox *Nashville::create7ButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("7th"));
    groupBox->setChecked(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    QStringList chord;
    chord <<"7";
    QVector<QPushButton*> b;
    for(int i = 0; i<chord.size(); i++){
        b.push_back(new QPushButton(chord[i]));
        b[i]->setFocusPolicy(Qt::NoFocus);
        hbox->addWidget(b[i]);
    }
    hbox->addStretch(1);
    vbox->addLayout(hbox);
    groupBox->setLayout(vbox);
    return groupBox;
}
QGroupBox *Nashville::create9ButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Extended"));
    groupBox->setChecked(true);
    //QHBoxLayout *hbox = new QHBoxLayout;
    //QVBoxLayout *vbox = new QVBoxLayout;
    QGridLayout *gbox = new QGridLayout;
    QStringList chord;
    QString flat = QChar(UNICODE_FLAT);
    QString sharp = QChar(UNICODE_SHARP);
    chord <<"6/9"<<"7"<<"9"<<flat+"9"<<sharp+"9"<<"add9"<<"11"<<sharp+"11"<<"add11"<<"13"<<flat+"13"<<"add13";
    QVector<QPushButton*> b;
    for(int i = 0; i<chord.size(); i++){
        b.push_back(new QPushButton(chord[i]));
        b[i]->setFocusPolicy(Qt::NoFocus);
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],chord[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handleChord(QString)));
    //hbox->addStretch(1);
    //gbox->addLayout(hbox);
    groupBox->setLayout(gbox);
    return groupBox;
}
QString Nashville::convertUnicodeToString(uint32_t symbol)
{
    QString str;
    QChar charArray[2];
    charArray[0] = QChar::highSurrogate(symbol);
    charArray[1] = QChar::lowSurrogate(symbol);
    str =  QString(charArray, 2);
    //qDebug()<<"USC4 :"<<QChar::decomposition(QChar::surrogateToUcs4(charArray[0],charArray[1]));
    return str;
}

/*
 * QGroupBox *Nashville::createSymbolButtonGroup()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Symbol"));
    groupBox->setChecked(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    QStringList symbol;
    QString triangle = QChar(0x25b2);
    QString triangleR = QChar(0x25b6);
    QString circle = QChar(0x25cf);
    QString flat = QChar(UNICODE_FLAT);
    QString sharp = QChar(UNICODE_SHARP);
    QString repeatl = QChar(119061);
    QString repeatr = QChar(0x1D107);
    QString note4 = QChar(0x2669);
    QString note8 = QChar(0x266a);
    symbol <<"<"<<"<<"<<"^"<<triangle<<triangleR<<circle<<flat<<sharp<<repeatl<<repeatr<<note4<<note8;
    QVector<QPushButton*> b;
    QFont f("arial");
    f.setBold(true);
    for(int i = 0; i<symbol.size(); i++){
        b.push_back(new QPushButton(symbol[i]));
        b[i]->setFocusPolicy(Qt::NoFocus);
        b[i]->setFont(f);
        hbox->addWidget(b[i]);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],symbol[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),n,SLOT(handleSymbol(QString)));

    hbox->addStretch(1);
    vbox->addLayout(hbox);
    groupBox->setLayout(vbox);
    return groupBox;
}*/
/*void Nashville::handleButton(QString group,QString symbol)
{

    n->handleButton(group,symbol);
}
*/
