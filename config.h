#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QWidget>

class Config : public QObject
{
    Q_OBJECT
private:
    int stringType;
    QString guitarType;
    QString documentType;
public:
    explicit Config(QObject *parent = 0);
    void setStringNumber(int i);
    void setGuitar(QString);
    void setDocument(QString);
    static int getStringNumber();
    static QString getGuitar();
    static QString getDocument();
signals:

public slots:
};

#endif // CONFIG_H
