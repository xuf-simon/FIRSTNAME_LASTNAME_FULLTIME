#include "mainwindow.h"

#include <QApplication>
#include "MapStructure.h"
#include "routingalgorithm.h"
#include <iostream>
#include <stdio.h>
#include "taskmodulecenter.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    TaskModuleCenter taskModuleCenter;
    taskModuleCenter.getTask();
    taskModuleCenter.createTask();

    return a.exec();
}
