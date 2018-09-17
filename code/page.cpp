#include "page.h"
#include <iterator>
#include <global.h>


Page::Page()
{

}
Page::Page(int x, int y, int w, int h, QScrollArea *scrollArea)
{
    print_init();
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    qDebug()<<w;
    qDebug()<<h;
    qDebug()<<height();
    qDebug()<<width();
    global_cursorsize = 10;
    doExport = false;
    scrollPos = 0;
    this->scrollArea = scrollArea;
    leftmargin = x+20;
    rightmargin = w-20;
    topmargin = y+100;
    bottommargin = h-20;
    stringNumber = number_of_strings;
    neckPosition.push_back(topmargin);
    cursorWidth = global_cursorsize;
    cursorHeight = 2*global_cursorsize;
    c = new Cursor(leftmargin,topmargin,cursorWidth,cursorHeight);
    setFixedSize(w,h);
    //adjustSize();
    setFocusPolicy(Qt::StrongFocus);
    artist = "Untitled";
    song = "Untitled";
    key = "";
    time = "";
    bar = scrollArea->verticalScrollBar();
    fileName = "Untitled";
}
void Page::print_init()
{   
    qDebug()<<type_of_document;
    qDebug()<<type_of_guitar;
    qDebug()<<number_of_strings;
}
/*Ble brukt i init når jeg lagret config i data.txt
 *     QString filename = "Data.txt";
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream in(&file);
        QString line;
        do {
            line = in.readLine();

            }
        while(!line.isNull());
    }
    file.close();
*/
/*    QPushButton *qpb;
    qpb = new QPushButton(tr("&Test"));
    qpb->setDefault(true);
    QDialogButtonBox *qdbb;
    qdbb = new QDialogButtonBox();
    qdbb->addButton(qpb,QDialogButtonBox::ActionRole);
    qDebug()<<"heia";
    connect(qdbb, SIGNAL(accepted()), this, SLOT(test()));
    QDialog *dialog = new QDialog();
    dialog->exec();
*/
//}
void test(){}
void Page::paintEvent(QPaintEvent *)
{
    QPalette pal;
    pal = palette();
    pal.setColor(QPalette::Background,Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    bool drawHelpGrid = false;
    //QPainter painter(this);
    QPainter painter(this);
    //painter.scale(2.5,2.5);
    QFont fname("Ume P Gothic C4",20);
    QFont fname2("Helvetica [Cronyx]",global_cursorsize);

    painter.setFont(fname);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::SolidLine);
    painter.drawText(100,40,"Artist:");
    painter.drawText(100,70,"Song:");
    painter.drawText(200,40,artist);
    painter.drawText(200,70,song);
    painter.drawText(rightmargin-250,40,"Key: ");
    painter.drawText(rightmargin-150,40,key);
    painter.drawText(rightmargin-250,70,"Time: ");
    painter.drawText(rightmargin-150,70,time);


    QFont fname3("Ubuntu",global_cursorsize);
    painter.setFont(fname3);

    //draw neck at position
    for(int i = 0; i<neckPosition.size(); i++)
    {

        for(int j = 0; j<stringNumber+3; j++)
        {
            if(j > stringNumber)
            {
                lastLine = neckPosition.at(i)+(j-2)*2*global_cursorsize;
                continue;
            }
            painter.drawLine(leftmargin,neckPosition.at(i)+j*2*global_cursorsize,rightmargin,neckPosition.at(i)+j*2*global_cursorsize);
        }
    }

    if(drawHelpGrid)
        for(int i = leftmargin; i<=rightmargin; i+=10)
            painter.drawLine(i,topmargin,i,bottommargin);

    //draw cursor
    painter.drawRect(*c);

    //scroll if needed
    doScroll();

    //draw notes from vector
    if(!n.isEmpty())
        for(int i = 0; i<n.size(); i++)
        {
            painter.drawText(n.at(i)->getPoint().x(),n.at(i)->getPoint().y(),global_cursorsize,2*global_cursorsize,Qt::AlignCenter,n.at(i)->getSymbol());
        }

    //test
    /*painter.setBrush(Qt::blue);
    QRect r = QRect(50,50,50,50);
    painter.drawRect(r);
    painter.setBrush(Qt::yellow);
    painter.drawArc(r,0,180*16);
    QRect r2 = QRect(100,50,50,50);
    painter.drawRect(r2);
    painter.drawArc(0,0,200,20,0,180*16);
    */
    //drawLegatoArc
    if(!leg.isEmpty())
    {
        QPen pe;
        pe.setWidth(2);
        pe.setCapStyle(Qt::FlatCap);
        painter.setPen(pe);
        int xoffset = cursorWidth/2;
        int yoffset = 0;//-cursorHeight/2;//cursorHeight/2;
        //int angleoffset =
        for(int i = 0; i<leg.size(); i++)
        {
            if(leg[i]->isComplete())
            {
                Legato *temp = leg[i];

                //painter.drawArc(temp->getX()+xoffset,temp->getY()-yoffset,temp->getW(),temp->getH(),temp->getStartAngle(),temp->getSpanAngle());
                painter.drawArc(temp->getX()+xoffset,temp->getY()-temp->getH()/3,temp->getW(),temp->getH(),temp->getStartAngle(),temp->getSpanAngle());
            }
        }
    }
    if(!slideup.isEmpty())
    {
        QPen pe;
        pe.setWidth(2);
        pe.setCapStyle(Qt::FlatCap);
        painter.setPen(pe);
        int xoffset = cursorWidth/2;
        int yoffset = 0;//-cursorHeight/2;//cursorHeight/2;

        for(int i = 0; i<slideup.size(); i++)
        {
            if(slideup[i]->isComplete())
            {
                Slide *temp = slideup[i];
                painter.drawLine(temp->getX()+cursorWidth,temp->getY()+cursorHeight-cursorHeight/3,temp->getX()+temp->getW(),temp->getY()+cursorHeight/3);
            }
        }
    }if(!slidedown.isEmpty())
    {
        QPen pe;
        pe.setWidth(2);
        pe.setCapStyle(Qt::FlatCap);
        painter.setPen(pe);
        int xoffset = cursorWidth/2;
        int yoffset = 0;//-cursorHeight/2;//cursorHeight/2;

        for(int i = 0; i<slidedown.size(); i++)
        {
            if(slidedown[i]->isComplete())
            {
                Slide *temp = slidedown[i];
                painter.drawLine(temp->getX()+cursorWidth,temp->getY()+cursorHeight/3,temp->getX()+temp->getW(),temp->getY()+cursorHeight-cursorHeight/3);
            }
        }
    }

}

void Page::keyPressEvent(QKeyEvent *event)
{
    QString e = event->text();
    if(event->key()==Qt::Key_Right ||event->key()==Qt::Key_Space)
    {
        qDebug()<<"page_right";
        if(c->topLeft().x() < rightmargin)
        {
            c->translate(cursorWidth,0);
            update();
        }
      }
    if(event->key()==Qt::Key_Left)
    {
        if(c->topLeft().x()>leftmargin)
        {
            c->translate(-cursorWidth,0);
            update();
        }
    }
    if(event->key()==Qt::Key_Up)
    {
        if(c->topLeft().y()>topmargin)
        {
            c->translate(0,-cursorHeight);
            update();
        }
    }
    if(event->key()==Qt::Key_Down)
    {
        if(c->topLeft().y()<bottommargin)
        {
            if(c->topLeft().y()==lastLine)
            {
                neckPosition.push_back(neckPosition.last()+13*cursorHeight);

            }
            c->translate(0,cursorHeight);
            update();
        }
    }
    if(event->key()==Qt::Key_0 || event->key()==Qt::Key_1 || event->key()==Qt::Key_2||event->key()==Qt::Key_3
            || event->key()==Qt::Key_4 || event->key()==Qt::Key_5 || event->key()==Qt::Key_6 || event->key()==Qt::Key_7
            || event->key()==Qt::Key_8 || event->key()==Qt::Key_9 || event->key()==Qt::Key_A || event->key()==Qt::Key_B
            || event->key()==Qt::Key_C || event->key()==Qt::Key_E || event->key()==Qt::Key_F || event->key()==Qt::Key_G)
    {
        if(c->topLeft().x() < rightmargin && c->topLeft().x() >=leftmargin)
        {
            insertSymbol(e.at(0).toUpper(),c->topLeft());
            c->translate(cursorWidth,0);
        }
    }
    if(event->key()==Qt::Key_L)
    {
        if(leg.isEmpty())
        {
            qDebug()<<"was empty";
             leg.push_back(new Legato(c->topLeft()));
        }
        else
        {
            if(leg.last()->isComplete())
            {
                qDebug()<<"was complete, making new";
                leg.push_back(new Legato(c->topLeft()));
            }
            else
            {
                qDebug()<<"was not complete, setting second";
                leg.last()->setSecondPoint(c->topLeft());
            }
        }
    }
    if(event->key()==Qt::Key_R)
    {
        if(leg.isEmpty())
        {
            qDebug()<<"Legato vector is empty";
        }
        else
        {

            qDebug()<<"Legato vector size: "<<leg.size();
            for(int i = 0;i<leg.size();i++){
                qDebug()<<i;
                qDebug()<<leg.at(i)->getX();
                if(leg.at(i)->getX() == c->topLeft().x() && leg.at(i)->getY() == c->topLeft().y())
                {
                    qDebug()<<"Legato exist at this point";
                    leg.remove(i);
                }



            }
        }
    }
    /* Slide UP */
    if(event->key()==Qt::Key_U)
    {
        qDebug()<<"Slide Up";
        if(slideup.isEmpty())
        {
            qDebug()<<"Slide vector was empty";
            slideup.push_back(new Slide(c->topLeft()));

        }
        else
        {
            if(slideup.last()->isComplete())
            {
                qDebug()<<"was complete, making new";
                slideup.push_back(new Slide(c->topLeft()));
            }
            else
            {
                qDebug()<<"was not complete, setting second";
                slideup.last()->setSecondPoint(c->topLeft());
            }
        }
    }

    /* Slide Down */
    if(event->key()==Qt::Key_D)
    {
        qDebug()<<"Slide Up";
        if(slidedown.isEmpty())
        {
            qDebug()<<"Slide vector was empty";
            slidedown.push_back(new Slide(c->topLeft()));

        }
        else
        {
            if(slidedown.last()->isComplete())
            {
                qDebug()<<"was complete, making new";
                slidedown.push_back(new Slide(c->topLeft()));
            }
            else
            {
                qDebug()<<"was not complete, setting second";
                slidedown.last()->setSecondPoint(c->topLeft());
            }
        }
    }

    if(event->key()==Qt::Key_Delete)
        clearNote(c->topLeft());
    /*To use implement "insert" mode backspace should maybe change every notes coordinate after current position (not place in vector) by x=-10 and
    * and also include lineshift per 10 tabs (little difficult, but not impossible...is it worth it?)
    */
    if(event->key()==Qt::Key_Backspace)
    {
        if(c->topLeft().x()>leftmargin)
        {
            c->translate(-10,0);
            clearNote(c->topLeft());

        }
    }
    if(event->key()==Qt::Key_Plus)
    {
        global_cursorsize += 5;
        cursorHeight = 2*global_cursorsize;
        cursorWidth = global_cursorsize;
        c->setSize(QSize(cursorWidth,cursorHeight));
    }
    if(event->key()==Qt::Key_Minus)
    {
        global_cursorsize -= 5;
        cursorHeight = 2*global_cursorsize;
        cursorWidth  = global_cursorsize;
        c->setSize(QSize(cursorWidth,cursorHeight));
    }
}
void Page::insertSymbol(QChar symbol,QPoint point)
{
    clearNote(point);
    n.push_back(new Note(symbol,point));
    update();
}
Note* Page::clearNote(QPoint point)
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
void Page::drawCursor()
{


}

void Page::drawSymbol()
{

}

void Page::addTabs()
{
    //QPainter painter(this);

}

void Page::setTitle()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Artist"),QLineEdit::Normal,QDir::home().dirName(), &ok);
    if(ok && !text.isEmpty())
        artist = text;
    update();
    text.clear();
    text = QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Song"),QLineEdit::Normal,QDir::home().dirName(), &ok);
    if(ok && !text.isEmpty())
        song = text;
    update();
}
void Page::setKey()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Key"),QLineEdit::Normal,QDir::home().dirName(), &ok);
    if(ok && !text.isEmpty())
        key = text;
    update();
}

void Page::save()
{
    qDebug()<<"size of n"<<n.size();
    fileName = QFileDialog::getSaveFileName((QWidget* )0, "Save document", QString(), "*.txt");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".txt"); }
    generateGrid();
    qDebug()<<"size of grid"<<grid.size();
    QFile file( fileName );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream<<"PROGRAM:PSGT"<<endl;
        stream<<"VERSION:1.0"<<endl;
        stream<<"FILENAME:"<<fileName<<endl;
        stream<<"ARTIST:"<<artist<<endl;
        stream<<"SONG:"<<song<<endl;
        stream<<"KEY:"<<key<<endl;
        stream<<"TIME:"<<time<<endl;
        stream<<"STRINGS:10"<<endl;
        stream<<"START"<<endl;
        for(int i = 0; i<grid.size(); i++)
        {
            for(int j = 0; j<150; j++)
            {
                if(!grid[i][j]->getSymbol().isNull())
                    stream << grid[i][j]->getSymbol();
                else{stream<<" ";}
            }
            stream<<endl;
        }
        stream<<"STOP";
    }
    file.close();
}
void Page::setTime()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Key"),QLineEdit::Normal,QDir::home().dirName(), &ok);
    if(ok && !text.isEmpty())
        time = text;
    update();
}

void Page::doScroll()
{
    if(c->topLeft().y()==topmargin)
        bar->setSliderPosition(0);
    else
    {
    scrollArea->ensureVisible(c->topLeft().x(),c->topLeft().y());
    }
    update();
}
QVector<QVector<Note*>>  Page::generateGrid()
{
    //generate
    QVector<QVector <Note*>> yvector(lastLine);
    for(int i = 0; i<yvector.size(); i++) {
        QVector<Note*> xvector(150);
        for(int j = 0; j<xvector.size(); j++)
        {
            xvector[j] = new Note();
        }
        yvector[i] = xvector;
    }

    //fill
    for(int i = 0; i<n.size();i++)
    {
        QChar sym = n[i]->getSymbol();
        int y_index = n[i]->getPoint().y();
        int x_index = n[i]->getPoint().x();
        y_index = (y_index-100)/20;
        x_index = (x_index-20)/10;
        yvector[y_index].insert(x_index,n[i]);

    }
    grid = yvector;
    return yvector;
}

void Page::exportPDF()
{
    generateGrid();

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("/home/anders/testtab.pdf");
    printer.setPageSize(QPrinter::A4);
    qDebug()<<"printer width: "<<printer.width();
    qDebug()<<"printer height: "<<printer.height();
    QPalette pal;
    pal = palette();
    pal.setColor(QPalette::Background,Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    QPainter painter(&printer);
    painter.scale(6.4,6.4);

    QFont fname("Ume P Gothic C4",2);
    QFont fname2("Helvetica [Cronyx]",1);

    painter.setFont(fname);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::SolidLine);
    painter.drawText(100,40,"Artist:");
    painter.drawText(100,70,"Song:");
    painter.drawText(200,40,artist);
    painter.drawText(200,70,song);
    painter.drawText(rightmargin-250,40,"Key: ");
    painter.drawText(rightmargin-150,40,key);
    painter.drawText(rightmargin-250,70,"Time: ");
    painter.drawText(rightmargin-150,70,time);

    QFont fname3("Ubuntu",1);
    painter.setFont(fname3);

    //draw neck at position
    int y = 0;
    int newPageCorrection = 0;
    bool new_page = true;
    new_page = false;
    for(int i = 0; i<neckPosition.size(); i++)
    {
        if(i!= 0 && i%8 == 0)
        {
            printer.newPage();
            newPageCorrection = neckPosition[i]-neckPosition[0];
        }

        for(int j = 0; j<stringNumber+3; j++)
        {
            if(j > stringNumber)
                {
                y++;
                continue;
            }
            painter.drawLine(leftmargin,neckPosition.at(i)-newPageCorrection+j*20,rightmargin,neckPosition.at(i)-newPageCorrection+j*20);
            for(int x = 0; x<150; x++)
            {
                painter.drawText(leftmargin+x*10,neckPosition.at(i)-newPageCorrection+j*20,10,20,Qt::AlignCenter,grid[y][x]->getSymbol());
            }
            y++; //increment y for every new line ALWAYS
        }
    }

    if(!leg.isEmpty())
    {
        QPen pe;
        pe.setWidth(2);
        pe.setCapStyle(Qt::FlatCap);
        painter.setPen(pe);
        int xoffset = cursorWidth/2;
        int yoffset = 0;//cursorHeight/2;
        //int angleoffset =
        for(int i = 0; i<leg.size(); i++)
        {
            if(leg[i]->isComplete())
            {
                Legato *temp = leg[i];

                painter.drawArc(temp->getX()+xoffset,temp->getY()-temp->getH()/3,temp->getW(),temp->getH(),temp->getStartAngle(),temp->getSpanAngle());
                //painter.drawRect(temp->getX()+xoffset, temp->getY()-yoffset,temp->getW(),temp->getH());
                //painter.drawArc(temp->getX()+xoffset,temp->getY()-yoffset,temp->getW(),temp->getH()*0.5,temp->getStartAngle(),temp->getSpanAngle());
            }
        }
    }



    QMessageBox mb;
    mb.setText("Pdf document produced.");
    mb.exec();
}
void Page::quit()
 {
     QCoreApplication *app = QCoreApplication::instance();
     QMessageBox msgBox;
     msgBox.setText("The document has been modified.");
     msgBox.setInformativeText("Do you want to save your changes?");
     msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Save);
     int ret = msgBox.exec();
     switch (ret) {
     case QMessageBox::Save:
     {
         // Save was clicked
         save();
         app->quit();
         break;
     }
     case QMessageBox::Discard:
     {
         // Don't Save was clicked
         app->quit();
         break;
     }
     case QMessageBox::Cancel:
         // Cancel was clicked
         break;
     default:
         // should never be reached
         break;
     }
 }
 void Page::newProject()
 {
     save();
     n.clear();
     artist.clear();
     song.clear();
     update();
 }

void Page::open()
{
    int lastNote = 0;
    newProject();
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Project"), "/home/anders", tr("PSGT Files (*.txt)"));
    QFile file( fileName );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        QString line;
        line = stream.readLine();
        if(line.compare("PROGRAM:PSGT")==0)
          qDebug()<<"Valid file";
        line = stream.readLine();
        if(line.compare("VERSION:1.0")==0)
            qDebug()<<"Valid version";
        line = stream.readLine();
        if(line.contains("FILENAME:"))
        {
            QStringList list = line.split(':');
            if(list.size()==2)
            {
                fileName = list[1];
            }
        }
        line = stream.readLine();
        if(line.contains("ARTIST:"))
        {
            QStringList list = line.split(':');
            if(list.size()==2)
            {
                artist = list[1];
            }
        }
        line = stream.readLine();
        if(line.contains("SONG:"))
        {
            QStringList list = line.split(':');
            if(list.size()==2)
            {
                song = list[1];
            }
        }
        line = stream.readLine();
        if(line.contains("KEY:"))
        {
            QStringList list = line.split(':');
            if(list.size()==2)
            {
                key = list[1];
            }
        }
        line = stream.readLine();
        if(line.contains("TIME:"))
        {
            QStringList list = line.split(':');
            if(list.size()==2)
            {
                time = list[1];
            }
        }
        line = stream.readLine();
        if(line.contains("STRINGS:"))
        {
            QStringList list = line.split(':');
            if(list.size()==2)
            {
                QString temp = list[1];
                stringNumber = temp.toInt();
            }
        }
        line = stream.readLine();
        if(line.contains("START"))
        {
            QVector<QString> lines;
            do {
                line = stream.readLine();
                lines.push_back(line);

            } while(!line.isNull());
            for(int y = 0; y<lines.size(); y++)
            {
                if(lines[y].trimmed().isEmpty())
                    continue;
                QString temp = lines[y];
                for(int i = 0; i<temp.length(); i++)
                {
                    if(temp.at(i).isSpace())
                        continue;
                    QPoint poi(leftmargin+i*10,topmargin+y*20);
                    insertSymbol(temp.at(i),poi);
                    lastNote = y;
                }
            }

        }
    }
    file.close();
    while(lastNote+topmargin>neckPosition.last())
        neckPosition.push_back(neckPosition.last()+13*20);
    update();
}
bool Page::legato()
{

    return true;
}
