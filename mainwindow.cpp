#include <QWidget>
#include <QDebug>

#include "mainwindow.h"
#include "menuwidget.h"
#include "gamewidget.h"

/* A window to hold the widgets */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //create class objects for widgets
    MenuWidget *menuwidget = new MenuWidget(this);
    GameWidget *gamewidget = new GameWidget(this);

    //create widgetstack to display widgets
    widgetstack = new QStackedWidget(this);
    widgetstack->addWidget(menuwidget);
    widgetstack->addWidget(gamewidget);
    widgetstack->setCurrentIndex(0);
    setCentralWidget(widgetstack);

    connect(menuwidget, SIGNAL(startsignal()),this , SLOT(changewidget()));
    connect(gamewidget, SIGNAL(backsignal()),this , SLOT(changewidget()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::changewidget()
{
    qDebug() << "change widget";
    if (widgetstack->currentIndex()==0)
    {
        widgetstack->setCurrentIndex(1);
    }else{
        widgetstack->setCurrentIndex(0);

    }

}
