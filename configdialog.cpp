#include <QtWidgets>
#include "configdialog.h"
//#include "global.h"
QString type_of_document;
QList<QString> document = {"Nashville Number System","Tab Editor","Chord Editor","Song Editor"};
QString type_of_guitar;
int number_of_strings;
ConfigDialog::ConfigDialog()
{
    createMenu();
    createHorizontalGroupBox();
    //createStringChoiceBox();
    createStringComboBox();
    createGuitarComboBox();
    //createGridGroupBox();
    //createFormGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                               "in the top-level layout."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox);
   // mainLayout->addWidget(stringChoiceBox);
    mainLayout->addWidget(guitarGroupBox);
    mainLayout->addWidget(stringGroupBox);
    //mainLayout->addWidget(gridGroupBox);
    //mainLayout->addWidget(formGroupBox);
    //mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}
void ConfigDialog::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
}
void ConfigDialog::createHorizontalGroupBox()
{
    QSignalMapper* mapper = new QSignalMapper(this);
    horizontalGroupBox = new QGroupBox(tr("Document Configuration"));
    QHBoxLayout *layout = new QHBoxLayout;
    QString a = "hei";
    for (int i = 0; i < NumButtons; ++i) {
        buttons[i] = new QPushButton(document[i]);
        layout->addWidget(buttons[i]);
        connect(buttons[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(buttons[i],i);
    }
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(handle_button(int)));

    horizontalGroupBox->setLayout(layout);
    //connect(buttons[0],SIGNAL(clicked()),this,SLOT(enableNashville()));
    //connect(buttons[1], SIGNAL(clicked()), this, SLOT(enableGuitar()));

}
/*void ConfigDialog::createStringChoiceBox()
{
    stringChoiceBox = new QGroupBox(tr("Number of strings"));
    QHBoxLayout *layout = new QHBoxLayout;
    for(int i = 0; i<NumStringOptions; i++) {
        cbox[i] = new QCheckBox(tr("%1 strings").arg(i+4));
        layout->addWidget(cbox[i]);
    }
    stringChoiceBox->setLayout(layout);
    connect(cbox[1], SIGNAL(clicked(bool)), this, SLOT(toggled(bool)));
}*/

/*choose number of strings menu*/
void ConfigDialog::createStringComboBox()
{
    QStringList ns;
    ns <<"4 Strings"<<"5 Strings"<<"6 Strings"<<"7 Strings"<<"8 Strings"<<"9 Strings"<<"10 Strings";
    stringGroupBox = new QGroupBox(tr("Strings"));
    stringGroupBox->setEnabled(false);
    QHBoxLayout *layout = new QHBoxLayout;
    stringComboBox = new QComboBox();
    stringComboBox->addItems(ns);
    //stringComboBox->setEnabled(false);
    layout->addWidget(stringComboBox);
    stringGroupBox->setLayout(layout);
    connect(stringComboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [=](int index){
        option_string=index+4;
        number_of_strings = index+4;

    });


}
void ConfigDialog::createGuitarComboBox()
{
    QStringList guitars;
    guitars<<"Choose a guitar"<<"Electric Guitar"<<"Pedal Steel Gutiar"<<"Mandolin"<<"Banjo";
    guitarGroupBox = new QGroupBox(tr("Guitars"));
    guitarGroupBox->setEnabled(false);
    QHBoxLayout *layout = new QHBoxLayout;
    guitarComboBox = new QComboBox();
    //guitarComboBox->setEnabled(false);
    guitarComboBox->addItems(guitars);
    layout->addWidget(guitarComboBox);
    guitarGroupBox->setLayout(layout);
    //connect(guitarComboBox, SIGNAL(currentIndexChanged(int i)), this, SLOT(enableString()));
    connect(guitarComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [=](int index){
        option_guitar=index;
        type_of_guitar="Electric";
        stringGroupBox->setEnabled(true);});
}

void ConfigDialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Grid layout"));
    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < NumGridRows; ++i) {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
        lineEdits[i] = new QLineEdit;
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }

    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
                                 "grid layout."));
    layout->addWidget(smallEditor, 0, 2, 4, 1);

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void ConfigDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
    formGroupBox->setLayout(layout);
}
void ConfigDialog::toggled(bool)
{
qDebug()<<"pressed";
}
void ConfigDialog::reject()
{
    exit(0);
}

/*void ConfigDialog::accept()
{
    //type_of_document= "hei";
    QString filename = "/home/anders/Data.txt";
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream<<"option_document="<<option_document<<endl;
        stream<<"option_guitar="<<option_guitar<<endl;
        stream<<"option_string="<<option_string<<endl;
    }
    file.close();
    //accepted();

}
*/
void ConfigDialog::handle_button(int i)
{
    type_of_document = document[i];
    for(int j = 0; j<NumButtons;j++) {
        if(j == i) {
            buttons[j]->setDown(true);
            guitarGroupBox->setEnabled(false);
            stringGroupBox->setEnabled(false);
        }
        else
        {
            buttons[j]->setDown(false);
        }
    }
    if(i==1)
        guitarGroupBox->setEnabled(true);
}
