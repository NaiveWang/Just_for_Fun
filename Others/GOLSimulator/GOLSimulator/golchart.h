#ifndef GOLCHART_H
#define GOLCHART_H

#include <QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include "golcore.h"

QT_CHARTS_USE_NAMESPACE

class GOLChart : public QChartView
{
    Q_OBJECT
public:
    explicit GOLChart(GOLCore *core, QChartView *parent = 0);
    ~GOLChart();
    void ChartRefresh();
signals:

public slots:
private:
    GOLCore *core;
    QLineSeries *series;
    QChart *chart;
};

#endif // GOLCHART_H
