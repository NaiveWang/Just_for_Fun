#include "golcontrolpanel.h"

#include <QDebug>

void GOLControlPanel::GOLStep()
{
    if(core->mark_stall)
    {
        log->showMessage("World Stalled.");
        return;
    }
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
        static char s[16];
        sprintf(s,"%d",delay);
        log->showMessage(s);
        if(core->mark_stall)
        {
            log->showMessage("World Stalled.");
            break;
        }
        core->GOLNextFrame();
        disp->updateGL();chart->ChartRefresh();
        //
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
    //QString  qs = QFileDialog::getOpenFileName(NULL,tr("Open File"),"~",tr("GOL Save(*.gol)"));
    ///log->showMessage(qs);//QTBUG-33119
    core->LoadGame(s);
    core->mark_stall=0;
    log->showMessage("File Opened.");
    disp->resizeGL(0,0);
    disp->updateGL();
}

void GOLControlPanel::GOLSave()
{
    char *s = file_name.text().toLatin1().data();
    //qDebug()<<s;
    //save.exec();
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
        core->mark_stall=0;
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
        core->mark_stall=0;
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
void GOLControlPanel::confLog(int s)
{
    core->conf_log=s;
    if(s)
    {
        core->logInit();
        log->showMessage("Log Srart Recording");
    }
    else
    {
        core->logSave();
        log->showMessage("Log Saved");
    }
}

void GOLControlPanel::confBound(int s)
{
    core->conf_boundary = s;
}

void GOLControlPanel::confStall(int s)
{
    core->conf_stall=s;
    if(s) log->showMessage("Stall Checking Opened");
    else
    {
        log->showMessage("Stall Checking Closed");
        core->mark_stall=0;
    }
}
void GOLControlPanel::confGrid(int s)
{
    core->conf_grid = s;
    disp->updateGL();
}
void GOLControlPanel::release_stall_mark()
{
    core->mark_stall=0;
    log->showMessage("Stall Unlocked");
}
void GOLControlPanel::modClearList()
{
    this->mList.clear();
    core->moduleClear();
    dot.toggle();
    log->showMessage("Module List Cleared");
}
void GOLControlPanel::modChooseItem(int s)
{
    core->mod_current=s;
    qDebug()<<core->mod_current;
    log->showMessage("Choosing an Item");
}

void GOLControlPanel::modOpen()
{
    char *s = file_name.text().toLatin1().data();
    core->LoadMod(s);
    mList.addItem(s);
    log->showMessage("Add a Module to Inventory");
}

void GOLControlPanel::modSave()
{
    char *s = file_name.text().toLatin1().data();
    core->SaveMod(s);
    log->showMessage("Module Saved");
}

void GOLControlPanel::modeChange(bool s)
{
    if(mList.count())
    {
        disp->flip=s;
        if(s) log->showMessage("Draw Dots");
        else log->showMessage("Draw Modules");
    }
    else
    {
        log->showMessage("Warning : No Item in Module Inventory");
        dot.toggle();
    }

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
    file_name.setText("GGG.gol");
    speed.setRange(2,25000);
    speed.setAccelerated(true);
    //speed.setDisplayIntegerBase(500);
    color.setText("Life Span");
    boundary.setText("Boundry");
    ifLog.setText("Print Log");
    stall.setText("Stall Check");
    grid.setText("Grid");
    b_release_stall_mark.setText("Unlock");
    dot.setText("Draw Dot");
    dot.toggle();
    mod.setText("Draw Module");
    b_save_m.setText("Save as a module");
    b_open_m.setText("Open Module");
    b_clear_m.setText("ClearList");


    QObject::connect(&b_step,SIGNAL(clicked(bool)),this,SLOT(GOLStep()));
    QObject::connect(&b_save,SIGNAL(clicked(bool)),this,SLOT(GOLSave()));
    QObject::connect(&b_open,SIGNAL(clicked(bool)),this,SLOT(GOLOpen()));
    QObject::connect(&b_start,SIGNAL(pressed()),this,SLOT(GOLRun()));
    QObject::connect(&b_clear,SIGNAL(clicked(bool)),this,SLOT(GOLClear()));
    QObject::connect(&b_new,SIGNAL(clicked(bool)),this,SLOT(GOLNew()));
    QObject::connect(&b_ran,SIGNAL(clicked(bool)),this,SLOT(GOLRan()));
    QObject::connect(&color,SIGNAL(stateChanged(int)),this,SLOT(confColor(int)));
    QObject::connect(&boundary,SIGNAL(stateChanged(int)),this,SLOT(confBound(int)));
    QObject::connect(&ifLog,SIGNAL(stateChanged(int)),this,SLOT(confLog(int)));
    QObject::connect(&grid,SIGNAL(stateChanged(int)),this,SLOT(confGrid(int)));
    QObject::connect(&stall,SIGNAL(stateChanged(int)),this,SLOT(confStall(int)));
    QObject::connect(&b_release_stall_mark,SIGNAL(clicked(bool)),this,SLOT(release_stall_mark()));

    QObject::connect(&b_clear_m,SIGNAL(clicked(bool)),this,SLOT(modClearList()));
    QObject::connect(&b_save_m,SIGNAL(clicked(bool)),this,SLOT(modSave()));
    QObject::connect(&b_open_m,SIGNAL(clicked(bool)),this,SLOT(modOpen()));
    QObject::connect(&mod,SIGNAL(toggled(bool)),this,SLOT(modeChange(bool)));
    QObject::connect(&mList,SIGNAL(currentIndexChanged(int)),this,SLOT(modChooseItem(int)));


    layout.addWidget(&b_step,0,0,1,1);
    layout.addWidget(&b_clear,0,1,1,1);
    layout.addWidget(&b_start,0,2,1,1);
    layout.addWidget(&speed,0,3,1,1);
    layout.addWidget(&file_name,1,0,1,4);
    layout.addWidget(&b_save,2,0);
    layout.addWidget(&b_open,2,1);
    layout.addWidget(&b_new,2,2);
    layout.addWidget(&b_ran,2,3);

    layout.addWidget(&b_open_m,3,0,1,1);
    layout.addWidget(&b_save_m,3,1,1,2);
    layout.addWidget(&b_clear_m,3,3,1,1);

    layout.addWidget(&color,4,0);
    layout.addWidget(&grid,4,1);
    layout.addWidget(&boundary,4,2);
    layout.addWidget(&ifLog,4,3);

    layout.addWidget(&stall,5,0,1,1);
    layout.addWidget(&b_release_stall_mark,6,0,1,1);
    layout.addWidget(&dot,5,1,1,2);
    layout.addWidget(&mod,6,1,1,2);

    layout.addWidget(&mList,5,2,1,2);

    //layout.addWidget(&conf,5,0);
    this->setLayout(&layout);
}
GOLControlPanel::~GOLControlPanel()
{
    delete(dialog);
}
