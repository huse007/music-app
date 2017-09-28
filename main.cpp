#include "widget.h"
#include "nashville.h"
//#include "nash.h" //Endret til denne fra den over
#include <QApplication>
#include "configdialog.h"
#include <QtGlobal>

int main(int argc, char **argv)
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    ConfigDialog d;
    d.exec();
    Nashville *nas = new Nashville();
    //Nash *n = new Nash(); //Endret til byttet med den over
    Widget w;
    //Fjern når testing er ferdig
    //type_of_document=document[0];
    if(type_of_document==document[0])
    {
        //Endret alle disse fra nas
        nas->setWindowState(Qt::WindowMaximized);
        //nas->setStyleSheet("background-color:pink;");
        nas->show();
    }
    else
    {
        w.setWindowState(Qt::WindowMaximized);
        w.show();
    }


   a.exec();
    return 0;//a.exec();
}
