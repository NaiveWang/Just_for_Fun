#include "gollog.h"

GOLLog::GOLLog()
{
    this->showMessage("Welcome!!!");
    //this->show();
}
void GOLLog::PrintLog(char *s)
{
    static QString qs = QString::fromUtf8(s);
    this->showMessage(qs);
}
