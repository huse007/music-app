#include "widget.h"

/*Draw on QScrollArea no pages
*/
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal;
    t = new Title(0,0,550,100,"Pedal Steel Guitar Tabs");
    l = new Logo(0,0,200,200);
    scrollArea = new QScrollArea();
    p = new Page(0,0,1500,20000,scrollArea);
    qvbl = new QVBoxLayout();
    qhbl = new QHBoxLayout();

    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidget(p);

    qhbl->addWidget(t,0);
    qhbl->addWidget(l,0);

    qvbl->addLayout(qhbl);
    qvbl->addWidget(createPushButtonGroup());
    qvbl->addWidget(scrollArea,0);
    setLayout(qvbl);
}

Widget::~Widget()
{
exit(0);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    QString e = event->text();
    if(event->key()==Qt::Key_Right)
    {
        qDebug()<<"hei";
        addPage();
      }
}
void Widget::paintEvent(QPaintEvent *)
{
   // qDebug()<<"Widget->paintevent";

    QPainter painter(this);
    painter.setBrush(Qt::black);


}

QGroupBox* Widget::createPushButtonGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("MENU"));
    groupBox->setChecked(true);
    QPushButton *button1 = new QPushButton(tr("&New"));
    QPushButton *button2 = new QPushButton(tr("&Open"));
    QPushButton *button3 = new QPushButton(tr("&Save"));
    QPushButton *button4 = new QPushButton(tr("&Quit"));
    QPushButton *button5 = new QPushButton(tr("&Help"));
    QPushButton *button6 = new QPushButton(tr("&Doc"));
    QPushButton *button7 = new QPushButton(tr("&Key"));
    QPushButton *button8 = new QPushButton(tr("&Time"));
    QPushButton *button9 = new QPushButton(tr("&Export"));
    QPushButton *button10 = new QPushButton(tr("&Legato"));
    QPushButton *popupButton = new QPushButton(tr("&Strings"));
    QPushButton *document = new QPushButton(tr("&Document"));
    QCheckBox *checkbutton = new QCheckBox(tr("Nashville"));
    button1->setFocusPolicy(Qt::NoFocus);
    button2->setFocusPolicy(Qt::NoFocus);
    button3->setFocusPolicy(Qt::NoFocus);
    button4->setFocusPolicy(Qt::NoFocus);
    button5->setFocusPolicy(Qt::NoFocus);
    button6->setFocusPolicy(Qt::NoFocus);
    button7->setFocusPolicy(Qt::NoFocus);
    button8->setFocusPolicy(Qt::NoFocus);
    button9->setFocusPolicy(Qt::NoFocus);
    button10->setFocusPolicy(Qt::NoFocus);

    popupButton->setFocusPolicy(Qt::NoFocus);
    checkbutton->setFocusPolicy(Qt::NoFocus);
    document->setFocusPolicy(Qt::NoFocus);
    QMenu *menu = new QMenu(this);
    menu->addAction(tr("&6 Strings"));
    menu->addAction(tr("&7 Strings"));
    menu->addAction(tr("&8 Strings"));
    menu->addAction(tr("&10 Strings"));
    menu->addAction(tr("&12 Strings"));
    popupButton->setMenu(menu);
    QHBoxLayout *hbox1 = new QHBoxLayout;
    QHBoxLayout *hbox2 = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    hbox1->addWidget(button1);
    hbox1->addWidget(button2);
    hbox1->addWidget(button3);
    hbox1->addWidget(button4);
    hbox1->addWidget(button5);
    hbox2->addWidget(button6);
    hbox2->addWidget(button7);
    hbox2->addWidget(button8);
    hbox2->addWidget(button9);
    hbox2->addWidget(button10);
    hbox2->addWidget(popupButton);
    hbox2->addWidget(checkbutton);
    hbox2->addWidget(document);
    hbox1->addStretch(1);
    hbox2->addStretch(1);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);

    groupBox->setLayout(vbox);
    connect(button1, SIGNAL (released()), this, SLOT (handleButtonNew()));
    connect(button2, SIGNAL (released()), this, SLOT (handleButtonOpen()));
    connect(button3, SIGNAL (released()), this, SLOT (handleButtonSave()));
    connect(button4, SIGNAL (released()), this, SLOT (handleButtonQuit()));
    connect(button6, SIGNAL (released()), this, SLOT (handleButtonDoc()));
    connect(button7, SIGNAL (released()), this, SLOT (handleButtonKey()));
    connect(button8, SIGNAL (released()), this, SLOT (handleButtonTime()));
    connect(button9, SIGNAL (released()), this, SLOT (handleButtonExport()));
    connect(button10, SIGNAL (released()), this, SLOT (handleButtonLegato()));

    return groupBox;
}

void Widget::addPage()
{
   /* QPainter painter(p);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::SolidLine);
    painter.drawLine(0,0,1000,1000);
    update();
    qDebug()<<"Draw Lines";
    */
}

void clearLayout()
{
 //code
    //page_layout

}
void Widget::handleButtonNew()
{
    p->newProject();
}

void Widget::handleButtonOpen()
{
    p->open();
}

void Widget::handleButtonDoc()
{
qDebug()<<"Document";
p->setTitle();
}
void Widget::handleButtonKey()
{
    p->setKey();
}
void Widget::handleButtonSave()
{
    p->save();
}
void Widget::handleButtonQuit()
{
    p->quit();
}

void Widget::handleButtonTime()
{
    p->setTime();
}
void Widget::handleButtonExport()
{
    p->exportPDF();
}
void Widget::handleButtonLegato()
{
    p->legato();
}
