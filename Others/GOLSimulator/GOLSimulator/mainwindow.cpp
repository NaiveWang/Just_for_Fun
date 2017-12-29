#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::MainWindow)*/
{
    //ui->setupUi(this);
    this->setFixedSize(800,600);

    core = new GOLCore(9,9);//for test use.
    *core->map[0] = 1;
    //*(core->map[0] + 8) = 1;
    *(core->map[0] + 80) = 1;
    //*(core->map[0]+2)=1;

    log = new GOLLog();

    disp = new GOLDisplayer(core,log);
    cPanel = new GOLControlPanel(core);

    chart = new GOLChart(core);


    layout.addWidget(this->log,23,0,1,32);
    layout.addWidget(this->disp,0,0,23,23);
    layout.addWidget(this->cPanel,6,23,17,9);

    layout.addWidget(this->chart,0,23,6,9);

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
    //delete ui;
}
