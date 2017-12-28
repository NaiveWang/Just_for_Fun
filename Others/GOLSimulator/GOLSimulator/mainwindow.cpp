#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::MainWindow)*/
{
    //ui->setupUi(this);
    this->setFixedSize(800,600);
    layout.addWidget(&this->disp,0,0,23,23);
    layout.addWidget(&this->cPanel,0,23,17,9);
    layout.addWidget(&this->log,23,0,1,32);
    layout.addWidget(&this->chart,17,23,6,9);

    this->setLayout(&layout);
    this->disp.show();
    this->log.show();
    this->cPanel.show();
    this->chart.show();
    this->show();
}

MainWindow::~MainWindow()
{
    //delete ui;
}
