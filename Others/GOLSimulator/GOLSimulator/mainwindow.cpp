#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::MainWindow)*/
{
    //ui->setupUi(this);
    this->setFixedSize(1600,1020);

    core = new GOLCore(25,25);//for test use.
    //*core->map[0] = 1;
    //*(core->map[0] + 8) = 1;
    //*(core->map[0] + 80) = 1;
    //*(core->map[0]+2)=1;

    log = new GOLLog();

    disp = new GOLDisplayer(core,log);


    chart = new GOLChart(core);
    cPanel = new GOLControlPanel(core,log,disp,chart);

    layout.addWidget(this->log,23,23,1,9);
    layout.addWidget(this->disp,0,0,23,23);
    layout.addWidget(this->cPanel,0,23,13,9);

    layout.addWidget(this->chart,13,23,10,9);

    this->chart->ChartRefresh();
    this->setLayout(&layout);
    this->disp->show();
    this->log->show();
    this->cPanel->show();
    this->chart->show();
    this->show();
}

MainWindow::~MainWindow()
{
    delete(cPanel);
    delete(chart);
    delete(disp);
    delete(log);
    delete(core);
    //delete ui;
}
