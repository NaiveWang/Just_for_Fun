#include "golcontrolpanel.h"

GOLControlPanel::GOLControlPanel(GOLCore *core, QWidget *parent) : QWidget(parent)
{
    this->core = core;
    b_start.setText("Run");
    b_stop.setText("Stop");
    b_step.setText("Step");
    layout.addWidget(&b_start,0,0);
    layout.addWidget(&b_stop,0,1);
    layout.addWidget(&b_step,1,0);
    this->setLayout(&layout);
}
