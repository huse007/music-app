#ifndef SYMBOLDIALOG_H
#define SYMBOLDIALOG_H

#include <nash.h>
#include <nashville.h>
#include <QDialog>
#include <QSignalMapper>
#include <QGroupBox>
#include <QGridLayout>
#include <QStringList>
#include <QVector>
#include <QPushButton>
#include <QApplication>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGTH 2000
#define UNICODE_FLAT 0x266d
#define UNICODE_SHARP 0x266f
#define BUTTON_W 100
class Nash;
class Nashville;
class SymbolDialog : public QDialog
{
    Q_OBJECT
private:
    Nash* p_nash;
    Nashville* nashville;
    QVBoxLayout* vbox;
    QDialogButtonBox* buttonBox;
public:
    SymbolDialog(Nash* n);
    QGroupBox* createHorizontalTopSymbolBox();
    QGroupBox* createHorizontalPreSymbolBox();
    QGroupBox* createLeftSymbolBox();
    QGroupBox* createRightSymbolBox();
    QGroupBox* createHorizontalCenterSymbolBox();
};

#endif // SYMBOLDIALOG_H
