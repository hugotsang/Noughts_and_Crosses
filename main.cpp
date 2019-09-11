#include <QApplication>

#include "mainwindow.h"

/*Function name: main(int argc, char *argv[])   */
/*Parameter: int argc, char *argv[]             */
/*Return: exit integer                          */
/*Description: Runs application and create      */
/*             main window                      */
int main(int argc, char *argv[])
{
    //Creates instance of application
    QApplication a(argc, argv);

    MainWindow mainwindow;
    mainwindow.setStyleSheet("background-color:#313131;");
    mainwindow.resize(520, 800);
    mainwindow.show();

    return a.exec();
}
