#ifndef GOLLOG_H
#define GOLLOG_H

#include <QStatusBar>

class GOLLog : public QStatusBar
{
public:
    GOLLog();
    void PrintLog(char*);
};

#endif // GOLLOG_H
