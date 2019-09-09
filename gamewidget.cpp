#include "mainwindow.h"
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent)
{
    game_table = new QTableWidget(3, 3, this);

    new_button = new QPushButton("New game", this);
    new_button->setGeometry(200, 320, 100, 62);

    back_button = new QPushButton("Back", this);
    back_button->setGeometry(200, 320, 100, 62);
    connect(back_button, SIGNAL(released()), this, SLOT(backbutton()));

    QGridLayout *Gamelayout = new QGridLayout;
    Gamelayout->addWidget(game_table,0,0);
    Gamelayout->addWidget(back_button,1,0);
    Gamelayout->addWidget(new_button,1,1);
    setLayout(Gamelayout);


}

GameWidget::~GameWidget()
{
    delete game_table;
    delete back_button;
}


void GameWidget::backbutton(){
   qDebug() << "game button pressed";
    emit backsignal();
}
