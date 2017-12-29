#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "golchart.h"
#include "golcontrolpanel.h"
#include "goldisplayer.h"
#include "gollog.h"
#include "golcore.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    GOLChart *chart;
    GOLControlPanel *cPanel;
    GOLDisplayer *disp;
    GOLLog *log;
    QGridLayout layout;
    GOLCore *core;
};

#endif // MAINWINDOW_H
