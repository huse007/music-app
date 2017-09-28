#include "symboldialog.h"

SymbolDialog::SymbolDialog(Nash* n)
{
    //qApp->setStyleSheet("SymbolDialog--QPushButton {background-color: red;font-family:\"lastresort\";font-size:20pt;}");
    //qApp->setStyleSheet("SymbolDialog--QPushButton{color:red;font-size:20;font-family:\"lastresort\";}");
    setWindowTitle("Symbol Panel");
    p_nash = n;
    vbox = new QVBoxLayout();
    vbox->addWidget(createHorizontalTopSymbolBox());
    vbox->addWidget(createHorizontalPreSymbolBox());
    vbox->addWidget(createLeftSymbolBox());
    vbox->addWidget(createRightSymbolBox());
    vbox->addWidget(createHorizontalCenterSymbolBox());
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    vbox->addWidget(buttonBox);
    setLayout(vbox);
  //setWindowFlags(windowFlags() | Qt::WindowCloseButtonHint);

}

QGroupBox* SymbolDialog::createHorizontalTopSymbolBox()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Top Symbol"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList symbol;

    //QString note4 = QChar(0x2669);
    //QString note8 = QChar(0x266a);
    QString note1 = "note1";
    QString note2 = "note2";
    QString note4 = "note4";
    QString note8 = "note8";
    QString note16 = "note16";
    QString note32 = "note32";
    QString note64 = "note64";
    QString dnote8 = "dnote8";
    QString dnote16 = "dnote16";
    QString dot = "dot";
    QString push = "push";
    QString dpush = "dpush";
    QString hat = "hat";
    QString cutshort = "cutshort";
    QString coda = "coda";

    //QString dnote8 = "dnote8";
    //QString bnote8 = "bnote8";
    //QString note4 = nashville->convertUnicodeToString(0x1d15f);
    //QString note8 = nashville->convertUnicodeToString(0x1d160);
    //QString note16 = nashville->convertUnicodeToString(0x1d161);
    //QString pause1 = nashville->convertUnicodeToString(0x1d13B);
    //QString pause2 = nashville->convertUnicodeToString(0x1d13C);
    //QString pause4 = nashville->convertUnicodeToString(0x1d13D);
    //QString pause8 = nashville->convertUnicodeToString(0x1d13E);
    //QString pause16 = nashville->convertUnicodeToString(0x1d13F);
    //QString triangle = nashville->convertUnicodeToString(0x1D149);
    //ushort *t = 0x1d161;
    //QString test = QString::setUtf16(t,2);
    symbol <<note1<<note2<<note4<<note8<<note16<<note32<<note64<<dnote8<<dnote16<<dot<<push<<dpush<<hat<<cutshort<<coda;
    QVector<QPushButton*> b;
    //QFont f("arial");
    //f.setBold(true);
    for(int i = 0; i<symbol.size(); i++){
        b.push_back(new QPushButton(QIcon(QPixmap("://qt_notes/"+symbol[i]+".png")),""));

        b[i]->setFont(QFont("lastresort",20));
       // b[i]->setMaximumWidth(BUTTON_W);
        b[i]->setFocusPolicy(Qt::NoFocus);
        //b[i]->setFont(f);
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],symbol[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),p_nash,SLOT(handleSymbol(QString)));
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(200);
    groupBox->setLayout(gbox);
    return groupBox;
}
QGroupBox* SymbolDialog::createHorizontalCenterSymbolBox()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Center Symbol"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList symbol;


    QString coda = "coda";
    QString segno = "segno";
    symbol <<coda<<segno;
    QVector<QPushButton*> b;
    for(int i = 0; i<symbol.size(); i++){
        b.push_back(new QPushButton(QIcon(QPixmap("://qt_notes/"+symbol[i]+".png")),""));
        b[i]->setFont(QFont("lastresort",20));
        b[i]->setFocusPolicy(Qt::NoFocus);
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],symbol[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),p_nash,SLOT(handleCenterSymbol(QString)));
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(200);
    groupBox->setLayout(gbox);
    return groupBox;
}
QGroupBox* SymbolDialog::createHorizontalPreSymbolBox()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Front Symbol"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList symbol;

    QString flat = QChar(UNICODE_FLAT);
    QString sharp = QChar(UNICODE_SHARP);
    QString pause = nashville->convertUnicodeToString(0x1d13D);
    QString repeatl = nashville->convertUnicodeToString(0x1d106);
    QString repeatr = nashville->convertUnicodeToString(0x1d107);
    QString barl = nashville->convertUnicodeToString(0x1D103);
    QString barr = nashville->convertUnicodeToString(0x1D102);
    QString ds = nashville->convertUnicodeToString(0x1D109);
    QString dc = nashville->convertUnicodeToString(0x1D10A);
    QString s = nashville->convertUnicodeToString(0x1D10B);
    QString coda = nashville->convertUnicodeToString(0x1D10C);
    symbol <<pause<<flat<<sharp<<ds<<dc<<s<<coda;
    QVector<QPushButton*> b;
    //QFont f("arial");
    //f.setBold(true);
    for(int i = 0; i<symbol.size(); i++){
        b.push_back(new QPushButton(symbol[i]));
       // b[i]->setMaximumWidth(BUTTON_W);
        b[i]->setFocusPolicy(Qt::NoFocus);
        b[i]->setFont(QFont("lastresort",20));
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],symbol[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),p_nash,SLOT(handlePreSymbol(QString)));
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(200);
    groupBox->setLayout(gbox);
    return groupBox;
}
QGroupBox* SymbolDialog::createLeftSymbolBox()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Left Symbol"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList symbol;
    QString repeatl = nashville->convertUnicodeToString(0x1d106);
    QString repeatr = nashville->convertUnicodeToString(0x1d107);
    QString barl = nashville->convertUnicodeToString(0x1D103);
    QString barr = nashville->convertUnicodeToString(0x1D102);
    QString ds = nashville->convertUnicodeToString(0x1D109);
    QString dc = nashville->convertUnicodeToString(0x1D10A);
    QString s = nashville->convertUnicodeToString(0x1D10B);
    QString coda = nashville->convertUnicodeToString(0x1D10C);
    symbol <<repeatl<<barl<<ds<<dc<<s<<coda;
    QVector<QPushButton*> b;
    //QFont f("arial");
    //f.setBold(true);
    for(int i = 0; i<symbol.size(); i++){
        b.push_back(new QPushButton(symbol[i]));
       // b[i]->setMaximumWidth(BUTTON_W);
        b[i]->setFocusPolicy(Qt::NoFocus);
        b[i]->setFont(QFont("lastresort",20));
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],symbol[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),p_nash,SLOT(handleLeftSymbol(QString)));
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(200);
    groupBox->setLayout(gbox);
    return groupBox;
}
QGroupBox* SymbolDialog::createRightSymbolBox()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QGroupBox *groupBox = new QGroupBox(tr("Right Symbol"));
    groupBox->setChecked(true);
    QGridLayout *gbox = new QGridLayout;
    QStringList symbol;
    QString repeatl = nashville->convertUnicodeToString(0x1d106);
    QString repeatr = nashville->convertUnicodeToString(0x1d107);
    QString barl = nashville->convertUnicodeToString(0x1D103);
    QString barr = nashville->convertUnicodeToString(0x1D102);
    QString ds = nashville->convertUnicodeToString(0x1D109);
    QString dc = nashville->convertUnicodeToString(0x1D10A);
    QString s = nashville->convertUnicodeToString(0x1D10B);
    QString coda = nashville->convertUnicodeToString(0x1D10C);
    symbol <<repeatr<<barr<<ds<<dc<<s<<coda;
    QVector<QPushButton*> b;
    //QFont f("arial");
    //f.setBold(true);
    for(int i = 0; i<symbol.size(); i++){
        b.push_back(new QPushButton(symbol[i]));
       // b[i]->setMaximumWidth(BUTTON_W);
        b[i]->setFocusPolicy(Qt::NoFocus);
        b[i]->setFont(QFont("lastresort",20));
        gbox->addWidget(b[i],i/3,i%3);
        connect(b[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(b[i],symbol[i]);
    }
    connect(mapper,SIGNAL(mapped(QString)),p_nash,SLOT(handleRightSymbol(QString)));
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(200);
    groupBox->setLayout(gbox);
    return groupBox;
}
/*QGroupBox* SymbolDialog::createHorizontalSymbolBox()
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
    connect(mapper,SIGNAL(mapped(QString)),nash,SLOT(handleChord(QString)));
    //gbox->setVerticalSpacing(0);
    //gbox->setMargin(0);
    groupBox->setMaximumWidth(400);
    groupBox->setMaximumHeight(100);
    groupBox->setLayout(gbox);
    return groupBox;
}*/
