#ifndef GOLCONTROLPANEL_H
#define GOLCONTROLPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>

#include "golcore.h"
#include "gollog.h"
#include "goldisplayer.h"
#include "golchart.h"

class GOLControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit GOLControlPanel(
            GOLCore *core,
            GOLLog *log,
            GOLDisplayer *disp,
            GOLChart *chart,
            QWidget *parent = 0);

signals:

public slots:
    void GOLStep();
    void GOLRun();
    void GOLStop();
    void GOLOpen();
    void GOLSave();
    void GOLNew();
private:
    GOLCore *core;
    GOLLog *log;
    GOLDisplayer *disp;
    GOLChart *chart;

    QGridLayout layout;
    QPushButton b_start,b_stop,b_step;
    QSpinBox speed;
    QPushButton b_new,b_open,b_save;
    QLineEdit file_name;
    QGroupBox conf;

    char lock_run;
    //char lock_
};

#endif // GOLCONTROLPANEL_H
