#include "golcontrolpanel.h"

#include <QDebug>

void GOLControlPanel::GOLStep()
{
    core->GOLNextFrame();
    disp->updateGL();
    chart->ChartRefresh();
}

void GOLControlPanel::GOLRun()
{
    /*delay = speed.value();
    this->lock_run = true;
    QThreadPool::globalInstance()->start(runner);**/
    //Qt Thread is malfuntion
    delay=speed.value();
    while(delay--)
    {

        core->GOLNextFrame();
        disp->updateGL();
        chart->ChartRefresh();
        //QThread::usleep(delay);
    }
}
void GOLControlPanel::GOLClear()
{
    core->GOLClear();
    disp->updateGL();
}

void GOLControlPanel::GOLOpen()
{
    char *s = file_name.text().toLatin1().data();
    core->LoadGame(s);
    log->showMessage("File Opened.");
    disp->resizeGL(0,0);
    disp->updateGL();
}

void GOLControlPanel::GOLSave()
{
    char *s = file_name.text().toLatin1().data();
    //qDebug()<<s;
    core->SaveGame(s);
    log->showMessage("File Saved.");
}

void GOLControlPanel::GOLNew()
{
    dialog->dialogOpen();
    dialog->exec();
    if(temp_x)
    {
        core->NewGame(temp_x,temp_y);
        disp->resizeGL(0,0);
        disp->updateGL();
        log->showMessage("New World Created.");
    }
    else
    {
        log->showMessage("Canceled.");
    }

}
void GOLControlPanel::GOLRan()
{
    dialog->dialogOpen();
    dialog->exec();
    if(temp_x)
    {
        core->RanGame(temp_x,temp_y);
        disp->resizeGL(0,0);
        disp->updateGL();
        log->showMessage("New Random World Created, bias = 1/1");
    }
    else
    {
        log->showMessage("Canceled");
    }

}
void GOLControlPanel::confColor(int s)
{
    if(s) core->conf_color = 0;
    else core->conf_color = -1;
    //core->conf_color=~core->conf_color;
    disp->updateGL();
}
void GOLControlPanel::confLog()
{
    ;
}

void GOLControlPanel::confBound()
{
    ;
}

void GOLControlPanel::confCheck()
{
    ;
}

GOLControlPanel::GOLControlPanel(GOLCore *core,
                                 GOLLog *log,
                                 GOLDisplayer *disp,
                                 GOLChart *chart,
                                 QWidget *parent) : QWidget(parent)
{
    this->core = core;
    this->log = log;
    this->disp = disp;
    this->chart = chart;

    dialog = new SizeInputDialog(&temp_x,&temp_y);
    //runner = new GOLAutoRunner(core,disp,chart,&delay,&lock_run);

    //lock_run=0;
    //delay=500;//500ms

    b_start.setText("Run");
    b_clear.setText("Clear");
    b_step.setText("Step");
    b_save.setText("Save");
    b_open.setText("Open");
    b_new.setText("New");
    b_ran.setText("Random");
    file_name.setText("save.gol");
    speed.setRange(2,10000);
    speed.setAccelerated(true);
    //speed.setDisplayIntegerBase(500);
    color.setText("Life Span");
    boundary.setText("Boundry");
    ifLog.setText("Printing Log");
    checking.setText("Smart Checking");

    QObject::connect(&b_step,SIGNAL(clicked(bool)),this,SLOT(GOLStep()));
    QObject::connect(&b_save,SIGNAL(clicked(bool)),this,SLOT(GOLSave()));
    QObject::connect(&b_open,SIGNAL(clicked(bool)),this,SLOT(GOLOpen()));
    QObject::connect(&b_start,SIGNAL(pressed()),this,SLOT(GOLRun()));
    QObject::connect(&b_clear,SIGNAL(clicked(bool)),this,SLOT(GOLClear()));
    QObject::connect(&b_new,SIGNAL(clicked(bool)),this,SLOT(GOLNew()));
    QObject::connect(&b_ran,SIGNAL(clicked(bool)),this,SLOT(GOLRan()));
    QObject::connect(&color,SIGNAL(stateChanged(int)),this,SLOT(confColor(int)));

    layout.addWidget(&b_step,0,0,1,1);
    layout.addWidget(&b_clear,0,1,1,1);
    layout.addWidget(&b_start,1,0,1,1);
    layout.addWidget(&speed,1,1,1,1);
    layout.addWidget(&file_name,2,0,1,2);
    layout.addWidget(&b_save,3,0);
    layout.addWidget(&b_open,3,1);
    layout.addWidget(&b_new,4,0);
    layout.addWidget(&b_ran,4,1);
    layout.addWidget(&color,5,0);
    layout.addWidget(&boundary,6,0);
    layout.addWidget(&ifLog,7,0);
    layout.addWidget(&checking,8,0);
    //layout.addWidget(&conf,5,0);
    this->setLayout(&layout);
}
GOLControlPanel::~GOLControlPanel()
{
    delete(dialog);
}
