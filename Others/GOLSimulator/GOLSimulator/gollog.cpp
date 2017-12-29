#include "gollog.h"

GOLLog::GOLLog()
{
    this->showMessage("Welcome!!!");
    //this->showMessage("we");
    //this->show();
}
void GOLLog::PrintLog(char *s)
{
    QString qs = QString::fromUtf8(s);
    //this->clearMessage();
    this->showMessage(qs,1000);
}
