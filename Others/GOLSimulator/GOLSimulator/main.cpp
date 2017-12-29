#include "mainwindow.h"
#include <QApplication>

#define VERSION "Cellular Automata Simulator V0.7 beta"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(VERSION);
    w.show();

    return a.exec();
}
