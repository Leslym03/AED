#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
#include "avl.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
