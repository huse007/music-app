#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <settings.h>
#include <config.h>
#include "page.h"
#include "global.h"
#include <QSignalMapper>
//#include <QTextEdit>
//#include <QDialogButtonBox>
//#include <QVBoxLayout>
//#include <QBoxLayout>
//#include <QLayout>
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QCheckBox;
class QComboBox;
class Config;

extern QString type_of_document;
extern QString type_of_guitar;
extern int number_of_strings;
extern QString dtype;
class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    ConfigDialog();
private:
    int option_string;
    int option_guitar;
    int option_document; //nashville=0,tab=1
    void createMenu();
    void createHorizontalGroupBox();
    void createStringChoiceBox();
    void createStringComboBox();
    void createGuitarComboBox();
    void createGridGroupBox();
    void createFormGroupBox();
    enum { NumGridRows = 3, NumButtons = 4 ,NumStringOptions = 7};
    QMenuBar *menuBar;
    QGroupBox *horizontalGroupBox;
    QGroupBox *stringChoiceBox;
    QGroupBox *stringGroupBox;
    QGroupBox *guitarGroupBox;
    QGroupBox *gridGroupBox;
    QGroupBox *formGroupBox;
    QTextEdit *smallEditor;
    QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QCheckBox *cbox[NumStringOptions];
    QDialogButtonBox *buttonBox;
    QComboBox *stringComboBox;
    QComboBox *guitarComboBox;

    QMenu *fileMenu;
    QAction *exitAction;
signals:

public slots:
    void toggled(bool);
    //void accept();
    void reject();
    //void enableGuitar();
    //void enableString(int index);
    //void disableGuitar();
    //void enableNashville();
    void handle_button(int i);
};

#endif // CONFIGDIALOG_H
