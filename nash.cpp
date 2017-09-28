#include "nash.h"

Nash::Nash(Nashville *parent) : Nashville(parent)
{

}
Nash::Nash(int x, int y, int w, int h, QScrollArea *scrollArea)
{

    this->x = 100;
    this->y = 100;
    this->w = 200;
    this->h = 200;
    //this->scrollArea = scrollArea;
    //scrollArea->setWidget(this);
    this->scrollArea = scrollArea;


    //doExport = false;
    //scrollPos = 0;

    leftmargin = x+MARGIN_LEFT;
    rightmargin = w-MARGIN_RIGHT;
    topmargin = y+MARGIN_TOP;
    bottommargin = h-MARGIN_BOTTOM;
    neckPosition.push_back(topmargin);
    cursorWidth = 1.5*global_cursorsize;
    cursorHeight = 2*global_cursorsize;
    bigcursorHeigth = cursorHeight;
    bigcursorWidth = cursorWidth;
    minicursorWidth = 1.5*global_minicursorsize;
    minicursorHeight = 2*global_minicursorsize;
    c = new Cursor(INDENT_CURSOR,topmargin+10,cursorWidth,cursorHeight);
    lines.push_back(c->topLeft());
    setFixedSize(w,h);
    setFocusPolicy(Qt::StrongFocus);

    artist = "Untitled";
    song = "Untitled";
    key = "Unknown";
    time = "Unknown";

    line_vec.push_back(new Line("I",c->topLeft().y()));
    getLineFromCursor(c->topLeft());

    //ch.push_back(new Chord("1",c->topLeft()));
    //Chord *tmp = getChord(c->topLeft());
    //if(tmp!=NULL)
    //    tmp->setDiamond(false);

    update();
}

void Nash::paintEvent(QPaintEvent *)
{
    //qDebug()<<"Start paint";
    QPalette pal;
    pal = palette();
    pal.setColor(QPalette::Background,Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    //bool drawHelpGrid = false;
    QPainter painter(this);
    //painter.scale(2.5,2.5);
    QFont fname("Ume P Gothic C4",20);
    QFont fname2("Helvetica [Cronyx]",global_cursorsize);

    painter.setFont(fname);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::SolidLine);
    painter.drawText(INDENT_HEADER,40,"Artist:");
    painter.drawText(INDENT_HEADER,70,"Song:");
    painter.drawText(100,40,artist);
    painter.drawText(100,70,song);
    painter.drawText(rightmargin-250,40,"Key: ");
    painter.drawText(rightmargin-150,40,key);
    painter.drawText(rightmargin-250,70,"Time: ");
    painter.drawText(rightmargin-150,70,time);

//painter.drawLine(0,700,1190,700);painter.drawLine(100,0,100,1700);
    QFont fname3("Ubuntu",global_cursorsize*2,QFont::Bold);
    painter.setFont(fname3);
    //draw cursor
   bool drawcursor = true;
    //if(!c->isTop())
    //    painter.drawRect(*c);
    painter.setFont(QFont("LastResort",global_cursorsize*2));
    //QPixmap pix("://qt_notes/note2.png");
    //qDebug()<<"PIX: "<<pix.isNull();
    //painter.drawPixmap(INDENT_CURSOR,235,15,30,pix);
    //UNICODE TEST

    /*QString fil("://qt_notes/SegnoTeken.svg");
    QSvgRenderer bilde(fil);
    QPainter *painter2 = new QPainter(this);
    bilde.setViewBox(QRect(c->topLeft(),c->bottomRight()));
    bilde.render(painter2);
    QPoint ap(500,500);
    painter.drawPixmap(ap,QIcon(fil).pixmap(QSize(global_cursorsize,global_cursorsize*2)));
    */
    //help grid
    if(false)
    {
        for(int i = 0; i<lines.size(); i++)
        {
            painter.setBrush(QColor(0,0,50,70));
            painter.drawRect(INDENT_CURSOR-20,lines.at(i).y()-CURSOR_HEIGHT,getWidth()-INDENT_CURSOR-20-1,CURSOR_HEIGHT*4);
            painter.setBrush(QColor(0,0,255,70));
            painter.drawRect(INDENT_CURSOR-20,lines.at(i).y()-global_cursorsize*3,getWidth()-INDENT_CURSOR-20-1,cursorHeight);
        }
    }
    painter.setBrush(Qt::NoBrush);
    //getLines();
    /* Draws the chor etc..
     * It also make a square around it.
     * The QRect is calculated firs from the numbers boundingrect
     * and then adjust it if there exist top symbols
     * Todo: make rect for all part of chord tail, head number, etc.
     * Then do one check in the end: lowest topleftx, highest toprightx, lowest y, highest y
     * and finally make one rect. When c.istopleft don't draw cursor, but highlight top rect*/
    if(!ch.isEmpty())
        for(int i = 0; i<ch.size(); i++)
        {
           // qDebug()<<"Number: "<<ch.at(i)->getNumber();
            QRect box;
            QPoint p(ch.at(i)->getPoint());
            painter.setFont(fname3);
            painter.drawText(ch.at(i)->getPoint().x(),ch.at(i)->getPoint().y()+global_cursorsize*2,ch.at(i)->getNumber());
            QRect number_rect(painter.fontMetrics().boundingRect(ch.at(i)->getNumber()));
            number_rect.translate(p.x(),p.y()+global_cursorsize*2);
            box = number_rect;
            QVector<QString> tmp = ch.at(i)->getTopSymbol();
            int x_point = p.x()+global_cursorsize;
            int total_width = 0;
            int highest_symbol = 0;
            for(int k = 0; k<tmp.size(); k++){
                total_width += QPixmap("://qt_notes/"+tmp.at(k)+".png").width();
                int tmp_h = QPixmap("://qt_notes/"+tmp.at(k)+".png").height();
                if(tmp_h>highest_symbol)
                    highest_symbol=tmp_h;
            }

            x_point -=total_width/2;
            QRect top_rect(x_point,p.y()-2*global_cursorsize,total_width,highest_symbol);
            box = box.united(top_rect);

            for(int j = 0; j<tmp.size(); j++)
            {
                QPixmap pm("://qt_notes/"+tmp.at(j)+".png");
                total_width += pm.width();
                painter.drawPixmap(x_point,p.y()-global_cursorsize*2,QPixmap("://qt_notes/"+tmp.at(j)+".png"));
                x_point+=pm.width();
                QPixmap *px = new QPixmap("://qt_notes/"+tmp.at(j)+".png");
            }

            //painter.drawRect(box);
            QRect tail_rect;
            if(!ch.at(i)->getTail().isNull())
            {
                painter.setFont(QFont("Ubuntu",POST_SIZE,QFont::Bold));
                QFontMetrics fm(painter.fontMetrics());
                tail_rect = fm.boundingRect(ch.at(i)->getTail());
                tail_rect.translate(QPoint(p.x()+global_cursorsize*1.4,p.y()+global_cursorsize*2));
                if(!ch.at(i)->isDiamond())
                    painter.drawText(p.x()+global_cursorsize*1.4,p.y()+global_cursorsize*2,ch.at(i)->getTail());
                else
                {
                    painter.setPen(QPen(Qt::black,2));
                    painter.setBrush(Qt::NoBrush);
                    QPoint center_point(p.x()+global_cursorsize/1.5,p.y()+global_cursorsize);

                    painter.translate(center_point.x(),center_point.y());
                    painter.rotate(45);
                    painter.drawRect(QRect(-cursorHeight*1.2/2,-cursorHeight*1.2/2,cursorHeight*1.2,cursorHeight*1.2));
                    painter.rotate(-45);
                    painter.translate(-center_point.x(),-center_point.y());
                    //painter.setFont(fname3);
                    painter.drawText(p.x()+global_cursorsize*2.1,p.y()+global_cursorsize*2,ch.at(i)->getTail());
                }
            }
            QRect front_rect;
            if(!ch.at(i)->getFront().isNull())
            {
                painter.setFont(QFont("lastresort",global_cursorsize*2));
                if(!ch.at(i)->isDiamond())
                    painter.drawText(p.x()-global_cursorsize*1.4,p.y()+global_cursorsize*2,ch.at(i)->getFront());
                else
                {
                    painter.drawText(p.x()-global_cursorsize*2.1,p.y()+global_cursorsize*2,ch.at(i)->getFront());
                }
                front_rect = painter.fontMetrics().boundingRect(ch.at(i)->getFront());
                front_rect.translate(p.x()-global_cursorsize*1.4,p.y()+global_cursorsize*2);
            }

            box = box.united(tail_rect);
            box = box.united(front_rect);
            box = box.marginsAdded(QMargins(10,10,10,10));
            painter.setPen(Qt::NoPen);
            painter.drawRect(box);
            painter.fillRect(box,QColor(0,0,255,20));
            painter.setPen(Qt::SolidLine);
            //painter.drawRect(*c);
            if(c->intersects(box))
            {
                qDebug()<<"chord "<<i<<"intersecting";
                c->moveTo(p);
                drawcursor = false;
                if(c->ct == c->cfree)
                {
                    c->ct = c->cbox;
                }

                if(c->ct == c->cbox)
                {
                    painter.drawRect(box);
                    qDebug()<<" cbox";
                }
                else if(c->ct == c->cnumber)
                {
                    painter.drawRect(number_rect.marginsAdded(QMargins(5,0,5,0)));
                    qDebug()<<" cnumber";
                }
                else if(c->ct == c->ctop && !ch.at(i)->getHat().isEmpty())
                {
                    painter.drawRect(top_rect.marginsAdded(QMargins(5,5,5,5)));
                    qDebug()<<" ctop";
                }
                else if(c->ct==c->ctop && ch.at(i)->getHat().isEmpty() && !ch.at(i)->getTail().isEmpty())
                {
                    painter.drawRect(tail_rect.marginsAdded(QMargins(5,5,5,5)));
                    c->ct = c->ctail;
                    qDebug()<<" top empty drawing tail";
                }
                else if(c->ct == c->ctail && !ch.at(i)->getTail().isEmpty())
                {
                    painter.drawRect(tail_rect.marginsAdded(QMargins(5,5,5,5)));
                    qDebug()<<" ctail";
                }
                else{
                    qDebug()<<" else draw box";
                    c->ct = c->cbox;
                    painter.drawRect(box);
                }
            }
            else
            {
                qDebug()<<"chord "<<i<<"not intersecting";
            }
        }
    painter.setBrush(Qt::black);
    if(drawcursor)
        painter.drawRect(*c);
    //draw part
    /*QPen pen_part(Qt::black,1);
    painter.setPen(pen_part);
    QFont part_font("Ubuntu",PART_SIZE,QFont::Bold);
    painter.setFont(part_font);
    QFontMetrics *fm = new QFontMetrics(painter.font());
    if(!line_vec.isEmpty())
        for(int i = 0; i<line_vec.size(); i++)
        {
            painter.setFont(part_font);
            painter.drawText(INDENT_HEADER,line_vec.at(i)->getPoint().y()+cursorHeight,line_vec.at(i)->getPart());
            painter.drawRect(INDENT_HEADER-5,line_vec.at(i)->getPoint().y()-5,fm->width(line_vec.at(i)->getPart())+10,cursorHeight+10);
            painter.setFont(QFont("lastresort",MARGINSYMBOL_SIZE));
            painter.drawText(70,line_vec.at(i)->getPoint().y()+global_cursorsize*2,line_vec.at(i)->getLSymbol());
            painter.drawText(rightmargin-15,line_vec.at(i)->getPoint().y()+global_cursorsize*2,line_vec.at(i)->getRSymbol());
        }
    delete fm;
    */
    //draw part pixmap
    if(!line_vec.isEmpty())
        for(int i = 0; i<line_vec.size();i++)
    {
        QPixmap pix_part("://qt_notes/"+line_vec.at(i)->getPart()+".png");
        //qDebug()<<line_vec.at(i)->getPart()<<" "<<pix_part.isNull();
        painter.drawPixmap(INDENT_HEADER,line_vec.at(i)->getPoint().y(),pix_part.width(),pix_part.height(),pix_part);
    }
    for(int i = 0; i<element.size();i++)
    {
        QPixmap pix_element("://qt_notes/"+element.at(i)->getElement()+".png");
        painter.drawPixmap(element.at(i)->getPoint().x(),element.at(i)->getPoint().y(),pix_element.width(),pix_element.height(),pix_element);
    }


    painter.setFont(fname3);
    //painter.drawText(10,100,"1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890");
    //draw notes from vector
    if(!n.isEmpty())
        for(int i = 0; i<n.size(); i++)
        {
            painter.drawText(n.at(i)->getPoint().x(),n.at(i)->getPoint().y()+global_cursorsize*2,n.at(i)->getSymbol());
        }
    //draw minor symbols
    if(!minor.isEmpty())
        for(int i = 0; i<minor.size(); i++)
        {
            painter.drawText(minor.at(i)->getPoint().x()+1.5*global_cursorsize/2, minor.at(i)->getPoint().y(),global_cursorsize,2*global_cursorsize,Qt::AlignCenter,minor.at(i)->getSymbol());
        }
    QFont fname4("Ubuntu",TOP_SIZE,QFont::Bold);
    painter.setFont(fname4);
    //draw top symbols from vector
    if(!top.isEmpty())
        for(int i = 0; i<top.size(); i++)
        {
            painter.drawText(top.at(i)->getPoint().x(),top.at(i)->getPoint().y(),TOP_SIZE,TOP_SIZE,Qt::AlignCenter,top.at(i)->getSymbol());
        }

    QFont fname42("Ubuntu",BIGSYMBOL_SIZE,QFont::Bold);
    painter.setFont(fname42);
    if(!bigSymbol.isEmpty())
        for(int i = 0; i<bigSymbol.size(); i++)
        {
            painter.drawText(bigSymbol.at(i)->getPoint().x(),bigSymbol.at(i)->getPoint().y(),TOP_SIZE,TOP_SIZE,Qt::AlignCenter,bigSymbol.at(i)->getSymbol());
        }
    /* DRAW CHORDS
     * (min,aug,...)
     * checks if diamond exist and increase the space if it does
     */

    QFont fname45("Ubuntu",POST_SIZE,QFont::Bold);
    painter.setFont(fname45);
    if(!chord.isEmpty())
        for(int i = 0; i<chord.size(); i++)
        {
            bool indent = false;
            if(!diam.isEmpty())
                for(int j = 0; j<diam.size(); j++)
                    if(diam.at(j).manhattanLength()-chord.at(i)->getPoint().manhattanLength()<30 &&
                            diam.at(j).manhattanLength()-chord.at(i)->getPoint().manhattanLength()>-30)
                    {
                        indent = true;
                    }
            if(indent)
                painter.drawText(chord.at(i)->getPoint().x()+15,chord.at(i)->getPoint().y(),chord.at(i)->getText());
            else
                painter.drawText(chord.at(i)->getPoint().x()+5,chord.at(i)->getPoint().y(),chord.at(i)->getText());
        }
    QFont fname5("Ubuntu",global_cursorsize/1.5,QFont::Bold);
    painter.setFont(fname5);
    //draw post symbols from vector
    if(!post.isEmpty())
        for(int i = 0; i<post.size(); i++)
        {
            painter.drawText(post.at(i)->getPoint(),post.at(i)->getSymbol());
        }

    //draw tetx
    QFont fname6("Ubuntu",global_cursorsize/2,QFont::Bold);
    painter.setFont(fname6);
    if(!txt.isEmpty())
    {
        for(int i = 0; i<txt.size(); i++)
        {
            //qDebug()<<txt.at(i)->getText();
            painter.drawText(txt.at(i)->getPoint().x()+0.5*cursorWidth,txt.at(i)->getPoint().y(),global_cursorsize*2,2*global_cursorsize,Qt::AlignCenter,txt.at(i)->getText());
        }
    }
//    QPainterPath path;
    painter.setBrush(Qt::NoBrush);
    QPen pen_square(Qt::black,1);
    painter.setPen(pen_square);
    if(!rect.isEmpty())
        for(int i = 0; i<rect.size(); i++)
        {
            painter.drawRect(rect.at(i)->adjusted(-global_cursorsize/1.5,-1.5*global_cursorsize,8.5*global_cursorsize,0.4*global_cursorsize));
        }
    QPen pen_diamond(Qt::black,2);
    painter.setPen(pen_diamond);
    if(!diam.isEmpty())
        for(int i = 0; i<diam.size(); i++)
        {
            QPoint cen(diam.at(i));
            painter.translate(cen.x(),cen.y());
            painter.rotate(45);
            painter.drawRect(QRect(-cursorHeight*1.2/2,-cursorHeight*1.2/2,cursorHeight*1.2,cursorHeight*1.2));
            painter.rotate(-45);
            painter.translate(-cen.x(),-cen.y());
            /*QPoint c(diam.at(i)->topLeft());
            qDebug()<<c.x()<<" "<<c.y();
            painter.drawRect(QRect(c.x(),c.y(),10,10));

           // painter.translate(c.x(),c.y());
           // painter.rotate(45);
            qreal rx = -(200 * 0.5);
            qreal ry = -(200 * 0.5);
            painter.drawRect(QRect(rx, ry, 200, 200));
           // painter.drawRect(QRect());
            //QMatrix matrix;
            //matrix.translate(diam.at(i)->left(),diam.at(i)->top());
            //matrix.rotate(45);
            //painter.setMatrix(matrix);
            //painter.drawRect(*diam.at(i));
        */}
/*
    //draw part
    QPen pen_part2(Qt::black,1);
    painter.setPen(pen_part2);
    QFont fname7("Ubuntu",PART_SIZE,QFont::Bold);
    painter.setFont(fname7);
    QFontMetrics *fm1 = new QFontMetrics(painter.font());
    if(!part.isEmpty())
        for(int i = 0; i<part.size(); i++)
        {
//            painter.drawText(INDENT_HEADER,part.at(i)->getPoint().y(),global_cursorsize*8,2*global_cursorsize,Qt::AlignVCenter,part.at(i)->getText());
            //painter.drawRect(QRect(INDENT_HEADER-5,part.at(i)->getPoint().y()-5,cursorWidth*part.at(i)->getText().length()+10,cursorHeight+10));
            painter.drawText(INDENT_HEADER,part.at(i)->getPoint().y()+cursorHeight,part.at(i)->getText());
            //qDebug()<<INDENT_HEADER,part.at(i)->getPoint().y();
            painter.drawRect(INDENT_HEADER-5,part.at(i)->getPoint().y()-5,fm1->width(part.at(i)->getText())+10,cursorHeight+10);
        }
    //qDebug()<<"End paint";*/
}
void Nash::keyPressEvent(QKeyEvent *event)
{
    static int cursorOption;
    static bool shift;

    //qDebug()<<shift;
QString e = event->text();

    if(event->modifiers() & Qt::ShiftModifier)
    {
        shift=!shift;

    }
    if(event->type()==QEvent::KeyPress)
    {
        QString e = event->text();

        if(event->key()==Qt::Key_Tab)
            if(c->topLeft().x()< rightmargin)
            {
                c->translate(cursorWidth*10,0);
                update();
            }
        if(event->key()==Qt::Key_Space)
        {
            c->moveCursorTabRight();
            update();
        }
        if(event->key()==Qt::Key_Right)
        {
            //qDebug()<<"page_right";
            if(c->topLeft().x() < rightmargin)
            {
                if(c->topLeft().x()<INDENT_CURSOR)
                    c->moveTo(INDENT_CURSOR,c->topLeft().y());
                else
                {
                    if(c->ct==c->cfree)
                        c->moveCursorRight();
                    else
                    {
                        c->moveCursorTabRight();
                        c->ct=c->cfree;
                    }
                    }


                update();
            }
            shift=!shift;
        }
        if(event->key()==Qt::Key_Left)
        {
            if(c->topLeft().x()>leftmargin)
            {
                if(c->topLeft().x()==INDENT_CURSOR)
                    c->moveTo(INDENT_HEADER,c->topLeft().y());
                else
                {
                    if(c->ct==c->cfree)
                        c->moveCursorLeft();
                    else
                    {
                        c->moveCursorTabLeft();
                        c->ct = c->cfree;
                    }
                }
                update();
            }
        }
        if(event->key()==Qt::Key_Up)
        {
            /*if(!c->isMini())
            {
                toggleCursor();
                update();
                return;
            }
            if(c->isMini())
            {
                toggleCursor();
                c->translate(0,-cursorHeight);
                //toggleCursor();
            }*/
            //må sjekke over også
            if(true)//c->topLeft().y()>topmargin+10 && c)
            {
                qDebug()<<"up: "<<c->ct;
               if(c->ct != c->cfree)
               {
                   qDebug()<<"c is not free";
                   if(c->ct==c->cbox){
                       c->ct = c->cnumber;
                       qDebug()<<"up: set cnumber";
                   }
                   else if(c->ct ==c->cnumber)
                   {
                       //qDebug()<<"cnumber";
                       if(getChord(c->topLeft()) == NULL)
                           qDebug()<<"ERROR: getchord returns null";
                       if(!getChord(c->topLeft())->getHat().isEmpty())
                       {
                          // qDebug()<<"set ctop";
                           c->ct = c->ctop;
                       }
                       else if(!getChord(c->topLeft())->getTail().isEmpty())
                       {
                       //qDebug()<<"set ctail";
                           c->ct = c->ctail;
                       }
                       else
                       {
                           c->ct = c->cbox;
                       }
                   }
                   else if(c->ct == c->ctop)
                       c->ct = c->ctail;
                   else if(c->ct == c->ctail)
                       c->ct = c->cbox;
                   else
                       qDebug()<<"key event c nothing";
               }
               else
               {
                   /* only moves cursor if it is located at an
                    * y() larger than first line (topmargin+10)*/
                   if(c->topLeft().y()>topmargin+10)
                   {
                       c->moveCursorGapUp();
                       qDebug()<<"movedUp";
                   }
               }
               update();
            }
        }
        if(event->key()==Qt::Key_Down)
        {
            c->ct = c->cfree;
            if(true)
            {
                c->setTop(false);
                c->moveCursorDown();
                //qDebug()<<c->topLeft().y();
                if(!isInLines(c->topLeft()))
                {
                    lines.push_back(c->topLeft());
                    line_vec.push_back(new Line(" ",c->topLeft().y()));
                }
                update();
                return;
            }
            else
            {
                c->moveCursorGapDown();
                c->setTop(true);

                update();
                return;
            }
            /*
            if(c->isMini())
            {
                toggleCursor();
                qDebug()<<"toggle";
                c->translate(0,cursorHeight);
                qDebug()<<"translated"<<cursorHeight;
                update();
                return;
            }
            if(!c->isMini())
                c->translate(0,1.5*cursorHeight);
                toggleCursor();

            if(c->topLeft().y()<bottommargin)
            {
                if(c->topLeft().y()==lastLine)
                {
                    neckPosition.push_back(neckPosition.last()+13*cursorHeight);

                }
                c->translate(0,cursorHeight);
                update();
            }
            */
        }
        if(event->key()==Qt::Key_Return)
        {
            if(c->isTop())
            {
                c->setTop(false);
                c->moveCursorDown();
                update();
             }
            if(!c->isTop())
            {
                c->moveCursorGapDown();
                c->moveCursorDown();
                update();
            }
        }
/*        if(!c->isMini())
            if(event->key()==Qt::Key_Return)
            {
                //toggleCursor();
                //c->translate(2*cursorWidth,cursorHeight);
                toggleCursorPost();
                update();
                return;
            }
        if(c->isMini())
            if(event->key()==Qt::Key_Return)
            {
                //c->translate(-2*cursorWidth,-cursorHeight);
                //toggleCursor();
                toggleCursorPost();
                update();
                return;
            }
            */
        if(c->isMini())
        {
            if(event->key()==Qt::Key_A || event->key()==Qt::Key_B || event->key()==Qt::Key_C || event->key()==Qt::Key_D ||
                    event->key()==Qt::Key_E || event->key()==Qt::Key_F || event->key()==Qt::Key_G || event->key()==Qt::Key_H ||
                    event->key()==Qt::Key_I || event->key()==Qt::Key_J || event->key()==Qt::Key_K || event->key()==Qt::Key_L ||
                    event->key()==Qt::Key_M || event->key()==Qt::Key_N || event->key()==Qt::Key_O || event->key()==Qt::Key_P ||
                    event->key()==Qt::Key_Q || event->key()==Qt::Key_R || event->key()==Qt::Key_S || event->key()==Qt::Key_T ||
                    event->key()==Qt::Key_U || event->key()==Qt::Key_V || event->key()==Qt::Key_W || event->key()==Qt::Key_X ||
                    event->key()==Qt::Key_Y || event->key()==Qt::Key_Z ||
                    event->key()==Qt::Key_1 || event->key()==Qt::Key_2 || event->key()==Qt::Key_3 || event->key()==Qt::Key_4 ||
                    event->key()==Qt::Key_5 || event->key()==Qt::Key_6 || event->key()==Qt::Key_7 || event->key()==Qt::Key_8 ||
                    event->key()==Qt::Key_9)
            {
               insertTop(e.at(0),c->topLeft());
               c->translate(cursorWidth,0);
               return;
            }
        }
        if(event->key()==Qt::Key_0 || event->key()==Qt::Key_1 || event->key()==Qt::Key_2||event->key()==Qt::Key_3
                || event->key()==Qt::Key_4 || event->key()==Qt::Key_5 || event->key()==Qt::Key_6 || event->key()==Qt::Key_7
                || event->key()==Qt::Key_8 || event->key()==Qt::Key_9 || event->key()==Qt::Key_B
                || event->key()==Qt::Key_E || event->key()==Qt::Key_F
                || event->key()==Qt::Key_G || event->key()==Qt::Key_Plus
                || event->key()==Qt::Key_Less || event->key()==Qt::Key_Period)
        {
            if(c->topLeft().x() < rightmargin && c->topLeft().x() >=leftmargin)
            {
                if(cursorOption==1)
                {
                    insertTop(e.at(0).toUpper(),c->topLeft());
                }
                else if(cursorOption==2){
                    insertPost(e.at(0).toUpper(),c->topLeft());
                }
                else{
                    //insertSymbol(e.at(0).toUpper(),c->topLeft());
                   insertNumber(e.at(0).toUpper(),c->topLeft());

                }
            }
        }

        if(event->key()==Qt::Key_Delete)
        {
            deleteChord(c->topLeft());
            update();
            //qDebug()<<c->bottomLeft()<<" "<<c->topLeft();
            //clearNote(c->topLeft());
            //clearTop(c->topLeft());
            //clearChord(c->bottomLeft());
            //clearPart(c->topLeft());
        }
        /*To use implement "insert" mode backspace should maybe change every notes coordinate after current position (not place in vector) by x=-10 and
    * and also include lineshift per 10 tabs (little difficult, but not impossible...is it worth it?)
    */
        if(event->key()==Qt::Key_Backspace)
        {
            if(c->topLeft().x()>leftmargin)
            {
                c->translate(-cursorWidth,0);
                clearNote(c->topLeft());

            }
        }

        if(event->key()==Qt::Key_Z)
        {
            if(cursorOption==2)
                cursorOption=0;
            else
                cursorOption++;

            switch(cursorOption){
            case 0:
                c->setNormalCursor();
                update();
                break;
            case 1:
                c->setTopCursor();
                update();
                break;
            case 2:
                c->setPostCursor();
                update();
                break;
            }
        }
        if(event->key()==Qt::Key_Minus) {
            insertMinor(e.at(0),c->topLeft());
        }
        if(event->key()==Qt::Key_Q) {
           //QRect *r = new QRect(c->center()-cursorWidth,c->center()-cursorHeight/2,cursorWidth*2,cursorHeight);
           //QRect *r = new QRect(c->topLeft(),c->bottomRight());
           rect.push_back(new QRect(c->topLeft(),c->bottomRight()));
           update();
           //rect.push_back(new QRect(c->topLeft()-cursorWidth,c->topLeft()-cursorWidth,3*cursorWidth,2*cursorHeight) )
       }
        if(event->key()==Qt::Key_U) {
           showSymbolDialog();
        }
        if(event->key()==Qt::Key_J) {
            insertText("maj7",c->topLeft());
        }
        if(event->key()==Qt::Key_D) {
            Chord* tmp = getChord(c->topLeft());
            if(tmp)
                if(tmp->isDiamond())
                    toggleDiamond(false);
                else
                    toggleDiamond(true);
            update();
        }
        if(event->key()==Qt::Key_M)
            insertPart("Mid-8",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_A)
            insertPart("TA",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_I)
            insertPart("Intro",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_V)
            insertPart("Verse",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_T)
            insertPart("Tag",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_C)
            insertPart("Chorus",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_H)
            insertPart("Channel",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_O)
            insertPart("Outro",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_S)
            insertPart("Solo",QPoint(INDENT_HEADER,c->topLeft().y()));
        if(event->key()==Qt::Key_B)
            insertPart("Bridge",QPoint(INDENT_HEADER,c->topLeft().y()));
    }
}
//fornyet
Chord* Nash::deleteChord(QPoint point)
{
    Chord* tmp = getChord(point);
    if(tmp)
        return ch.takeAt(ch.indexOf(tmp));
    return NULL;
}
/* This method is used for creating chord object
 * and setting the number*/
void Nash::insertNumber(QChar text, QPoint point)
{
    c->ct = c->cbox;
    qDebug()<<"insertNumber()";
    if(clearPoint(point))
        ch.push_back(new Chord(text,point));
    update();
}
void Nash::insertTail(QString txt, QPoint point)
{
    Chord *tmp = getChord(point);
    if(tmp!=NULL)
    {
        if(!tmp->getTail().isEmpty())
            tmp->setTail(tmp->getTail().append(txt));
        else
            tmp->setTail(txt);
        c->ct = c->ctail;
    }
    update();
}

/*GAMMELT*/
void Nash::insertSymbol(QChar symbol,QPoint point)
{
    qDebug()<<"insertSymbol()";
    clearNote(point);
    n.push_back(new Note(symbol,point));
    update();
}
//insertTop er fornyet
void Nash::insertTop(QString symbol,QPoint point)
{

    /*if(c->isTop())
    {
        //adjust point to not top and get chord
        point.setY(point.y()+CURSOR_HEIGHT*3);
    }*/
    Chord* tmp = getChord(point);
    if(tmp!=NULL)
    {
        QString t = tmp->getHat();
        //QChar u =

        //    tmp->setHat(tmp->getHat().append("  ").append(symbol));
        //else
            tmp->setHat(tmp->getHat().append(symbol));
            tmp->addTopSymbol(symbol);
    }
    c->ct = c->ctop;
    update();
}
/* If cursor is top
 * change point down to chordpoint
 * get the chord obj and set the variable*/
void Nash::insertPreSymbol(QString text)
{
    QPoint p(c->topLeft());

    if(c->isTop())
    {
        p.setY(p.y()+CURSOR_HEIGHT*3);
    }
    Chord* tmp = getChord(p);
    if(tmp!=NULL)
        tmp->setFront(text);
    update();
}

//insertBigSymbol er ikke fornyet
void Nash::insertBigSymbol(QChar symbol,QPoint point)
{
    bigSymbol.push_back(new Note(symbol,point));
    update();
}
//Disse er ikke fornyet (part kan være)
void Nash::insertPost(QChar symbol,QPoint point)
{
    post.push_back(new Note(symbol,point));
    update();
}
void Nash::insertMinor(QChar symbol,QPoint point)
{
    minor.push_back(new Note(symbol,point));
    update();
}
void Nash::insertText(QString text,QPoint point)
{
    txt.push_back(new Note(text,point));
    update();
}
void Nash::insertPart(QString text,QPoint point)
{
    qDebug()<<"insertPart()"<<line_vec.size();
    for(int i = 0; i<line_vec.size(); i++){
        //qDebug()<<"y pos: "<<line_vec.at(i)->getPoint().y()<<" "<<point.y();
        if(line_vec.at(i)->getPoint().y() == point.y())
        {
            line_vec.at(i)->setPart(text);
            //qDebug()<<"Setter ny text "<<text;
            update();
            return;
        }
    }
}
void Nash::insertCenterSymbol(QString symbol, QPoint point)
{
    if(clearPoint(point))
        element.push_back(new Element(symbol,point));
    update();
}
/* Not in use */
void Nash::insertChord(QString text,QPoint point)

{
    /*
    qDebug()<<"insertChord()";
    //qDebug()<<"*********";
    //qDebug()<<"x: "<<point.x()<<" y: "<<point.y();
    toggleCursorPost();
    int j = -1;
    int i = 0;
    for(i; i<chord.size();i++)
        if(chord.at(i)->getPoint().x() == point.x() && chord.at(i)->getPoint().y() == point.y()){
            j = i;
            //qDebug()<<"x: "<<chord.at(i)->getPoint().x()<<" y :"<<chord.at(i)->getPoint().y();
            break;
        }
    if(j==-1)
        chord.push_back(new Note(text,point));
    else {
        chord[i]->setText(chord[i]->getText().append(text));
        //QString s = chord.at(i)->getText();
        //qDebug()<<s;
        //s.append(text);

        //qDebug()<<s;
        //qDebug()<<"SSSSSSSSSSSSSS"<<chord[i]->getText();
    }
    update();
    */
}
//fornyet
void Nash::toggleDiamond(bool status)
{

    //diam.push_back(QPoint(c->center()));
    Chord *tmp = getChord(c->topLeft());
    if(tmp!=NULL)
        tmp->setDiamond(status);

}
//ikke fornyet
Note* Nash::clearNote(QPoint point)
{
    for(int i = 0; i<n.size(); i++)
    {
       if(n.at(i)->getPoint().x() == point.x() && n.at(i)->getPoint().y() == point.y())
       {
           Note *temp = n.takeAt(i);
           update();
           return temp;
       }
    }

    update();
    return NULL;
}
Note* Nash::clearTop(QPoint point)
{
    for(int i = 0; i<top.size(); i++)
    {
        if(top.at(i)->getPoint().x() == point.x() && top.at(i)->getPoint().y() == point.y())
        {
            Note *temp = top.takeAt(i);
            update();
            return temp;
        }
    }
    update();
    return NULL;
}
Note* Nash::clearChord(QPoint point)
{
    for(int i = 0; i<chord.size(); i++)
    {
        if(chord.at(i)->getPoint().x() == point.x() && chord.at(i)->getPoint().y() == point.y())
        {
            Note *temp = chord.takeAt(i);
            update();
            return temp;
        }
    }
    update();
    return NULL;
}

Note* Nash::clearPart(QPoint point)
{
    for(int i = 0; i<part.size(); i++)
    {
        if(part.at(i)->getPoint().x() == point.x() && part.at(i)->getPoint().y() == point.y())
        {
            Note *temp = part.takeAt(i);
            update();
            return temp;
        }
    }
    update();
    return NULL;
}

void Nash::handlePart(QString symbol)
{
    qDebug()<<"handlePart()";
    insertPart(symbol,QPoint(INDENT_HEADER,c->topLeft().y()));
}
void Nash::handleCenterSymbol(QString symbol)
{
    insertCenterSymbol(symbol,c->topLeft());
}

void Nash::handleSymbol(QString symbol)
{
    insertTop(symbol,c->topLeft());
}
void Nash::handleLeftSymbol(QString symbol)
{
    QPoint p(c->topLeft());
    int l = getLineFromCursor(p);
    for(int i = 0; i<line_vec.size(); i++)
    {
        if(line_vec.at(i)->getPoint().y()==p.y())
            line_vec.at(i)->setLSymbol(symbol);
    }
    update();
}
void Nash::handleRightSymbol(QString symbol)
{
    QPoint p(c->topLeft());
    int l = getLineFromCursor(p);
    for(int i = 0; i<line_vec.size(); i++)
    {
        if(line_vec.at(i)->getPoint().y()==p.y())
            line_vec.at(i)->setRSymbol(symbol);
    }
    update();
}
void Nash::handlePreSymbol(QString symbol)
{
    insertPreSymbol(symbol);
}

void Nash::handleChord(QString chord)
{
    insertTail(chord,c->topLeft());

}
void Nash::handleDocument(QString document)
{
    if(document.compare("Settings")==0)
        getSettings();
    if(document.compare("Export") == 0)
        exportPDF();
}

void Nash::getSettings()
    {
        settings = new QDialogButtonBox(QDialogButtonBox::Ok
                                        | QDialogButtonBox::Cancel);
        QDialog dialog;
        QVBoxLayout vbox(&dialog);
        QLabel label_artist("Artist");
        QLabel label_song("Song");
        QLabel label_key("Key");
        QLabel label_time("Time");
        QLineEdit art;
        QLineEdit son;
        QLineEdit k;
        QLineEdit tim;
        art.setText(artist);
        art.selectAll();
        son.setText(song);
        k.setText(key);
        tim.setText(time);
        vbox.addWidget(&label_artist);
        vbox.addWidget(&art);
        vbox.addWidget(&label_song);
        vbox.addWidget(&son);
        vbox.addWidget(&label_key);
        vbox.addWidget(&k);
        vbox.addWidget(&label_time);
        vbox.addWidget(&tim);
        vbox.addWidget(settings);
        dialog.setWindowTitle("Settings");
        dialog.setLayout(&vbox);
        QObject::connect(settings, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(settings, SIGNAL(rejected()), &dialog, SLOT(reject()));

        int result = dialog.exec();
        if(result == QDialog::Accepted){
            artist = art.text();
            song = son.text();
            key = k.text();
            time = tim.text();
        }
        delete settings;
    }

/* Not in use */
void Nash::toggleCursorPost()
{
    if(c->isMini())
    {
        c->translate(-bigcursorWidth,minicursorHeight-bigcursorHeigth);
        cursorHeight=bigcursorHeigth;
        cursorWidth=bigcursorWidth;
        c->setMini(false);
    }
    else
    {
        c->translate(bigcursorWidth,cursorHeight-minicursorHeight);
        cursorWidth=minicursorWidth;
        cursorHeight=minicursorHeight;

        update();
        c->setMini(true);
    }
    c->setHeight(cursorHeight);
    c->setWidth(cursorWidth);
}
void Nash::toggleCursor()
{
    if(c->isMini())
    {
        c->translate(0,cursorHeight);
        cursorWidth=cursorWidth*2;
        cursorHeight=cursorHeight*2;
        c->setMini(false);
    }
    else
    {
        c->translate(0,-cursorHeight);
        cursorWidth=cursorWidth/2;
        cursorHeight=cursorHeight/2;

        c->setMini(true);
    }
    c->setHeight(cursorHeight);
    c->setWidth(cursorWidth);
}
void Nash::moveCursorToTop()
{
    //NOT IN USE, see cursor class
    c->translate(0,-cursorHeight);
}
void Nash::moveCursorDown()
{
    //NOT IN USE, see cursor class
    c->translate(0,cursorHeight);
}

void Nash::exportPDF()
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("/home/anders/testnash.pdf");
    printer.setPageSize(QPrinter::A4);
    qDebug()<<"printer width: "<<printer.width();
    qDebug()<<"printer height: "<<printer.height();
    QPalette pal;
    pal = palette();
    pal.setColor(QPalette::Background,Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);


    QPainter painter(&printer);
    painter.scale(0.65,0.65);

    QFont fname("Ume P Gothic C4",20);
    QFont fname2("Helvetica [Cronyx]",1);

    painter.setFont(fname);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::SolidLine);
    painter.drawText(INDENT_HEADER,40,"Artist:");
    painter.drawText(INDENT_HEADER,70,"Song:");
    painter.drawText(90,40,artist);
    painter.drawText(90,70,song);
    painter.drawText(rightmargin-700,40,"Key: ");
    painter.drawText(rightmargin-630,40,key);
    painter.drawText(rightmargin-700,70,"Time: ");
    painter.drawText(rightmargin-630,70,time);

    QFont fname3("Ubuntu",30,QFont::Bold);
    //fname3.setPixelSize(28);
    painter.setFont(fname3);
    //painter.setPen(Qt::black);
    //painter.setBrush(Qt::black);

    //painter.drawLine(0,700,1190,700);
    //painter.drawLine(100,0,100,1700);
    //qDebug()<<"METRIC print"<<painter.fontMetrics().height();
    //painter.drawText(10,100,"1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890");
    //draw notes from vector
    if(!n.isEmpty())
        for(int i = 0; i<n.size(); i++)
        {
            painter.drawText(n.at(i)->getPoint().x(),n.at(i)->getPoint().y()+global_cursorsize*2,n.at(i)->getSymbol());
        }
    //draw part
    QFontMetrics *fm = new QFontMetrics(painter.font());
    painter.setBrush(Qt::NoBrush);
    if(!part.isEmpty())
        for(int i = 0; i<part.size(); i++)
        {
            //painter.drawText(QPoint(INDENT_HEADER,part.at(i)->getPoint().y()),part.at(i)->getText());
            painter.drawText(INDENT_HEADER,part.at(i)->getPoint().y()+cursorHeight,part.at(i)->getText());
            painter.drawRect(INDENT_HEADER-5,part.at(i)->getPoint().y()-5,fm->width(part.at(i)->getText())+10,cursorHeight+10);
        }
    QFont fname4("Ubuntu",18,QFont::Bold);
    //QFont fname4("Ubuntu",3,QFont::Bold);
    painter.setFont(fname4);
    if(!top.isEmpty())
        for(int i = 0; i<top.size(); i++)
        {
            //painter.drawText(top.at(i)->getPoint(),top.at(i)->getSymbol());
            painter.drawText(top.at(i)->getPoint().x(),top.at(i)->getPoint().y(),TOP_SIZE,TOP_SIZE,Qt::AlignCenter,top.at(i)->getSymbol());
        }
    if(!chord.isEmpty())
        for(int i = 0; i<chord.size(); i++)
        {
            painter.drawText(chord.at(i)->getPoint().x(),chord.at(i)->getPoint().y(),chord.at(i)->getText());
        }
    QMessageBox mb;
    mb.setText("Pdf document produced.");
    mb.exec();
}
//fornyet
Chord* Nash::getChord(QPoint p)
{
    //qDebug()<<"Chord size: "<<ch.size();
    for(int i = 0; i<ch.size(); i++)
        if(ch.at(i)->getPoint().x() == p.x() && ch.at(i)->getPoint().y() == p.y())
        {
            //qDebug()<<"Fant object fra punktet"<<i;
            return ch.at(i);
        }
    return NULL;
}
int Nash::getWidth()
{
    return w;
}

QVector<QPoint> Nash::getLines()
{
    //qDebug()<<"getLines()";
    //QVector<QPoint> lines;

    for(int i = 0; i<ch.size(); i++)
    {
        if(lines.isEmpty())
            lines.push_back(ch.at(i)->getPoint());
        else
        {
            bool exist = false;
            for(int j = 0; j<lines.size(); j++)
                if(ch.at(i)->getPoint().y()==lines.at(j).y())
                {
                    exist = true;
                }
            if(!exist)
                lines.push_back(ch.at(i)->getPoint());
        }
    }
   /*if(!lines.isEmpty())
        for(int k = 0; k<lines.size(); k++)
            qDebug()<<"k "<<lines.at(k).y();
    qDebug()<<lines.size();
    */
    return lines;
}
bool Nash::isInLines(QPoint p)
{
    for(int i = 0; i<lines.size(); i++)
        if(p.y() == lines.at(i).y())
            return true;
    return false;
}
int Nash::getLineFromCursor(QPoint p)
{
    int nline = p.y();
    //qDebug()<<"LINE NR: "<<nline;
    return 0;
}

void Nash::showSymbolDialog()
{
    SymbolDialog d(this);
    d.exec();
}
void Nash::showAbout()
{
    QMessageBox about;
    about.setIcon(QMessageBox::Information);
    //about.about(this,"About","Developer: Anders Huse");
    about.setWindowTitle("About");
    about.setTextFormat(Qt::RichText);
    about.setText("Nashville Numbering v1.0");
    about.setInformativeText("Developer: Anders Huse\nDocumentation: Anders Huse\nBug Report: trippeltintegralet@gmail.com\nVersion: 1.0\nDate: 21.sept 2017\n\nCopyright 2016-2017 The Huse Software Company Ltd. All rights reserved.\n\nThe program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.");
    about.addButton(QMessageBox::Ok);
    about.exec();
}
void Nash::showWhatIs()
{
    QMessageBox whatis;
    whatis.setWindowTitle("What is Nashville Numbering?");
    whatis.setText("Instead of writing the chords A B C D E F G, one can write them as 1 2 3 4 5 6 7.\n"
                   "So, if your song has a chord progression A B C, you can write them as 1 2 3 (in the key of A).\n\n"
                   "One advantage with this method is when you transpose the song to a different key.\n"
                   "Let's say you want to play B C D instead. Well, you can still say 1 2 3, but the key is now B and not A. ");
    whatis.addButton(QMessageBox::Ok);

    whatis.exec();
    /*
    QTableView *v = new QTableView;
    QStandardItemModel *model = new QStandardItemModel(2,3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1 Header")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2 Header")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));
    QStandardItem *firstRow = new QStandardItem(QString("ColumnValue"));
    model->setItem(0,0,firstRow);
    v->setFont(QFont("Times",20));

    v->setModel(model);
    v->setColumnWidth(30,30);
    v->setRowHeight(20,20);
    v->setSpan(2,2,2,2);
    v->setWindowTitle("Hei");
    v->show();
    */
}
bool Nash::comparePoints(QPoint p1, QPoint p2)
{
    if(p1.x()==p2.x()&&p1.y()==p2.y())
        return true;
    return false;
}

bool Nash::isPointBusy(QPoint point)
{
    for(int i = 0; i<element.size();i++)
        if(comparePoints(point,element.at(i)->getPoint()))
            return true;
    for(int i = 0; i<ch.size(); i++)
        if(comparePoints(point,ch.at(i)->getPoint()))
            return true;
}
bool Nash::clearPoint(QPoint point)
{
    qDebug()<<"clearPoint()";

    for(int i = 0; i<element.size();i++)
        if(comparePoints(point,element.at(i)->getPoint())){
            if(warningRemoveSymbol() == QMessageBox::Ok)
            {
                element.takeAt(i);
                return true;
            }
            else
                return false;
        }
    for(int i = 0; i<ch.size(); i++)
        if(comparePoints(point,ch.at(i)->getPoint())){
            //qDebug()<<"POPOP "<<warningRemoveSymbol();
            if(warningRemoveSymbol() == QMessageBox::Ok)
            {
                ch.takeAt(i);
                return true;
            }
            else
                return false;
        }
    return true;
}
int Nash::warningRemoveSymbol()
{
    QMessageBox msgBox;
    msgBox.setText("Symbol allready exist");
    msgBox.setInformativeText("Do you want to remove current symbol?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    return ret;
}
