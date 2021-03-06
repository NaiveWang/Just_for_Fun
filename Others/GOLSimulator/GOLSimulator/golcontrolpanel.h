#ifndef GOLCONTROLPANEL_H
#define GOLCONTROLPANEL_H

#include <QThread>

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QComboBox>

#include <stdio.h>

#include "golcore.h"
#include "gollog.h"
#include "goldisplayer.h"
#include "golchart.h"

/**class GOLAutoRunner : public QRunnable
{
public:
    GOLAutoRunner(
            GOLCore *core,
            GOLDisplayer *disp,
            GOLChart *chart,
            int *delay,
            const char* lock)
    {
        this->core=core;
        this->disp=disp;
        this->delay=delay;
        this->chart=chart;
        this->lock=lock;
    }

    void run()
    {
        //lock = true;
        while(lock)
        {
            core->GOLNextFrame();
            disp->updateGL();
            chart->ChartRefresh();
            QThread::usleep(*delay);
        }

    }
private:
    GOLCore *core;
    GOLDisplayer *disp;
    GOLChart *chart;
    int *delay;
    char const *lock;

};**/
class SizeInputDialog : public QDialog
{
    Q_OBJECT
public:
    SizeInputDialog(int *x,int *y)
    {
        this->x=x;
        this->y=y;
        note.setText("Input X and Y from left to the fucking right.");
        cancel.setText("Cancel");
        confirm.setText("Confirm");
        QObject::connect(&cancel,SIGNAL(clicked(bool)),this,SLOT(dialogCancel()));
        QObject::connect(&confirm,SIGNAL(clicked(bool)),this,SLOT(dialogConfirm()));

        edit_x.setRange(3,1000);
        edit_x.setAccelerated(true);
        edit_y.setRange(3,1000);
        edit_y.setAccelerated(true);

        layout.addWidget(&note,0,0,1,2);
        layout.addWidget(&edit_x,1,0,1,1);
        layout.addWidget(&edit_y,1,1,1,1);
        layout.addWidget(&cancel,2,0,1,1);
        layout.addWidget(&confirm,2,1,1,1);
        this->setLayout(&layout);
        //this->
    }
public slots:
    void dialogOpen()
    {
        this->show();
    }
    void dialogCancel()
    {
        *x=0;
        this->close();
    }
    void dialogConfirm()
    {
        *x=edit_x.value();
        *y=edit_y.value();
        this->hide();
    }
    //void dialogVanish();
private:
    QGridLayout layout;
    QPushButton cancel,confirm;
    QSpinBox edit_x,edit_y;
    QLabel note;
    int *x,*y;
};
////////////////////////////////////////////////////////
class SizeInputDialogRandom : public QDialog
{
    Q_OBJECT
public:
    SizeInputDialogRandom(int *x,int *y,int *bias)
    {
        this->x=x;
        this->y=y;
        this->bias=bias;
        note.setText("Input X, Y and Bias(from 0 to 65536)");
        cancel.setText("Cancel");
        confirm.setText("Confirm");
        QObject::connect(&cancel,SIGNAL(clicked(bool)),this,SLOT(dialogCancel()));
        QObject::connect(&confirm,SIGNAL(clicked(bool)),this,SLOT(dialogConfirm()));

        edit_x.setRange(3,1000);
        edit_x.setAccelerated(true);
        edit_y.setRange(3,1000);
        edit_y.setAccelerated(true);
        edit_bias.setRange(1,65536);
        edit_bias.setAccelerated(true);
        edit_bias.setValue(32768);

        layout.addWidget(&note,0,0,1,2);
        layout.addWidget(&edit_x,1,0,1,1);
        layout.addWidget(&edit_y,1,1,1,1);
        layout.addWidget(&edit_bias,2,0,1,1);
        layout.addWidget(&cancel,3,0,1,1);
        layout.addWidget(&confirm,3,1,1,1);
        this->setLayout(&layout);
        //this->
    }
public slots:
    void dialogOpen()
    {
        this->show();
    }
    void dialogCancel()
    {
        *x=0;
        this->close();
    }
    void dialogConfirm()
    {
        *x=edit_x.value();
        *y=edit_y.value();
        *bias=edit_bias.value();
        this->hide();
    }
    //void dialogVanish();
private:
    QGridLayout layout;
    QPushButton cancel,confirm;
    QSpinBox edit_x,edit_y;
    QSpinBox edit_bias;
    QLabel note;
    int *x,*y,*bias;
};
//////////////////////////////////////////////////////////////////////////
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
    ~GOLControlPanel();

signals:

public slots:
    void GOLStep();
    void GOLRun();
    void GOLClear();
    void GOLOpen();
    void GOLSave();
    void GOLNew();
    void GOLRan();
    void confColor(int);
    void confLog(int);
    void confBound(int);
    void confStall(int);
    void confGrid(int);
    void release_stall_mark();

    void modClearList();
    void modOpen();
    void modSave();
    void modChooseItem(int);
    void modeChange(bool);
private:
    GOLCore *core;
    GOLLog *log;
    GOLDisplayer *disp;
    GOLChart *chart;

    SizeInputDialog *dialog;
    SizeInputDialogRandom *dialogR;
    //GOLAutoRunner *runner;

    QGridLayout layout;
    QPushButton b_start,b_clear,b_step;
    QSpinBox speed;
    QPushButton b_new,b_open,b_save,b_ran,b_open_m,b_save_m,b_clear_m;
    QLineEdit file_name;
    //QGroupBox conf;
    QCheckBox color,boundary,ifLog,stall,grid;
    QPushButton b_release_stall_mark;
    QRadioButton dot,mod;
    QComboBox mList;

    //QFileDialog openf;

    //char lock_run;
    int delay;
    int temp_x,temp_y;
    int temp_bias;
    //char lock_
};

#endif // GOLCONTROLPANEL_H
