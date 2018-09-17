#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{

}
void Settings::setNumStrings(int i)
{
    numStrings = i;
}
int Settings::getNumStrings()
{
    return numStrings;
}
