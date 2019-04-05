#include "mainwindow.h"
#include "painter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    //w.show();

    Painter p;
    p.show();

    return a.exec();
}
