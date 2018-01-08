#include "mainwindow.h"
#include <QApplication>

#define VERSION "Cellular Automata Simulator V1.1 alpha"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(VERSION);
    w.show();

    return a.exec();
}
