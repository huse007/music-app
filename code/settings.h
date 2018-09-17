#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QWidget>

class Settings : public QObject
{
    Q_OBJECT
private:
    int numStrings;
public:
    explicit Settings(QObject *parent = 0);
    void setNumStrings(int i);
    int getNumStrings();
signals:

public slots:
};

#endif // SETTINGS_H
