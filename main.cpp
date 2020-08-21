#include "mainwindow.h"
#include <QApplication>
#include "MapStructure.h"
#include "routingalgorithm.h"
#include <iostream>
#include <stdio.h>
#include "taskmodulecenter.h"

#include "chart.h"
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    Chart *chart = new Chart;
    chart->init();

    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);
    window.setCentralWidget(&chartView);

   // chart->test();


    window.resize(400, 400);
    window.show();

    TaskModuleCenter taskModuleCenter;
    taskModuleCenter.getTask();
    taskModuleCenter.createTask(chart);

    return a.exec();
}
