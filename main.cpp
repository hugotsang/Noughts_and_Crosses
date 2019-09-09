#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Creates instance of application
    QApplication a(argc, argv);

    MainWindow mainwindow;
    mainwindow.resize(520, 700);
    mainwindow.show();

    return a.exec();
}
