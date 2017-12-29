#include "golchart.h"

GOLChart::GOLChart(GOLCore *core, QChartView *parent) : QChartView(parent)
{
    //this->QChartView(&chart);
    this->core = core;
    this->chart=new QChart();
    this->series = new QLineSeries();
    series->append(0,1);
    series->append(1,3);series->append(6,0);
    chart->addSeries(series);
    chart->createDefaultAxes();
    this->setChart(chart);
    this->setFixedSize(5,3);
    this->setRenderHint(QPainter::Antialiasing);

}
void GOLChart::ChartRefresh()
{
    delete this->series;
    this->series = new QLineSeries();
    for(int i=0;i<CACHES;i++)
    {
        series->append(i,core->alive[i]);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();
    this->setChart(chart);
}
