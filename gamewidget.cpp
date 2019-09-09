#include "mainwindow.h"
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent)
{

    back_button = new QPushButton("Back", this);
    back_button->setGeometry(200, 320, 100, 62);
    connect(back_button, SIGNAL(released()), this, SLOT(backbutton()));

    QGridLayout *Gamelayout = new QGridLayout;
    Gamelayout->addWidget(title,0,0);
    Gamelayout->addWidget(back_button,1,0);
    setLayout(Gamelayout);


}

GameWidget::~GameWidget()
{
    delete title;
    delete back_button;
}


void GameWidget::backbutton(){
   qDebug() << "game button pressed";
    emit backsignal();
}
