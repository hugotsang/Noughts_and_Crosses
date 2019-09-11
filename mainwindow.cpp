#include <QWidget>
#include <QDebug>

#include "mainwindow.h"
#include "menuwidget.h"
#include "gamewidget.h"

/*Function name: MainWindow(QWidget *parent)    */
/*Parameter: QWidget *parent                    */
/*Return: None                                  */
/*Description: Create an instance of MainWindow */
/*             widget                           */
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

/*Function name: ~MainWindow()                  */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Destructor for MainWindow        */
MainWindow::~MainWindow()
{
}

/*Function name: changewidget()                 */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Changes current display widget   */
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
