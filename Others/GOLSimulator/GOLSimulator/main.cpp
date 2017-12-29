#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Cellular Automata Simulator V0.5 beta");
    w.show();

    return a.exec();
}
