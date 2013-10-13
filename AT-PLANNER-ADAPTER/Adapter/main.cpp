#include <QApplication>
#include "utils.h"
#include <stdio.h>
#include <iostream>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlannerIteraction pi("/123");
    QGraphicsScene pScene; // ToDo: скорее всего, нужно будет переопределять QGraphicsScene
    pi.getPlan(); // ToDo: где-то тут запилить вызов функции добавления объектов из QList в QGraphicsScene
    QGraphicsView pView(&pScene);
    pView.show();
    return a.exec();
}
