#include "golcontrolpanel.h"
void GOLControlPanel::GOLStep()
{
    core->GOLNextFrame();
    disp->updateGL();
    chart->ChartRefresh();
}

void GOLControlPanel::GOLRun()
{
    ;
}

void GOLControlPanel::GOLStop()
{
    ;
}

void GOLControlPanel::GOLOpen()
{
    ;
}

void GOLControlPanel::GOLSave()
{
    ;
}

void GOLControlPanel::GOLNew()
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



    b_start.setText("Run");
    b_stop.setText("Stop");
    b_step.setText("Step");
    b_save.setText("Save");
    b_open.setText("Open");
    b_new.setText("New");

    QObject::connect(&b_step,SIGNAL(clicked(bool)),this,SLOT(GOLStep()));

    layout.addWidget(&b_start,0,0,1,1);
    layout.addWidget(&b_stop,0,1,1,1);
    layout.addWidget(&b_step,1,0,1,1);
    layout.addWidget(&speed,1,1,1,1);
    layout.addWidget(&file_name,2,0,1,2);
    layout.addWidget(&b_save,3,0);
    layout.addWidget(&b_open,3,1);
    layout.addWidget(&b_new,4,0);
    layout.addWidget(&conf,5,0);
    this->setLayout(&layout);
}
