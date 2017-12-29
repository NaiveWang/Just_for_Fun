#ifndef GOLCONTROLPANEL_H
#define GOLCONTROLPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "golcore.h"
class GOLControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit GOLControlPanel(GOLCore *core, QWidget *parent = 0);

signals:

public slots:
private:
    GOLCore *core;
    QGridLayout layout;
    QPushButton b_start,b_stop,b_step;
};

#endif // GOLCONTROLPANEL_H
