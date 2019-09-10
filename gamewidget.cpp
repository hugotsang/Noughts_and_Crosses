#include "mainwindow.h"
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent)
{
    int i, j;

    turn = Oturn;

    score_text = new QLabel(this);
    score_text->setText("noughts:1 crosses:0");
    score_text->setGeometry(10, 10, 200, 50);

    turn_text = new QLabel(this);
    if (turn == 0){
        turn_text->setText("noughts turn");
    }else{
        turn_text->setText("crosses turn");
    }
    turn_text->setGeometry(10, 10, 200, 50);

    game_table = new QTableWidget(3, 3, this);
    game_table->verticalHeader()->setVisible(false);
    game_table->horizontalHeader()->setVisible(false);

    for (i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            game_button[i][j] = new QPushButton(this);
            game_button[i][j]->setGeometry(0, 0, 50, 50);
            game_table->setCellWidget(i, j, game_button[i][j]);
            table_state[i][j] = 2; // 2 is used for cell being empty
            connect(game_button[i][j], SIGNAL(released()), this, SLOT(gamebutton()));
        }
    }

    new_button = new QPushButton("New game", this);
    new_button->setGeometry(200, 320, 100, 62);
    connect(new_button, SIGNAL(released()), this, SLOT(newbutton()));

    back_button = new QPushButton("Back", this);
    back_button->setGeometry(200, 320, 100, 62);
    connect(back_button, SIGNAL(released()), this, SLOT(backbutton()));

    QGridLayout *Gamelayout = new QGridLayout;
    Gamelayout->addWidget(score_text, 0, 0, 1, 2);
    Gamelayout->addWidget(turn_text, 1, 0, 1, 2);
    Gamelayout->addWidget(game_table, 2, 0, 1, 2);
    Gamelayout->addWidget(back_button, 3, 0);
    Gamelayout->addWidget(new_button, 3, 1);
    setLayout(Gamelayout);


}

GameWidget::~GameWidget()
{
    delete game_table;
    delete back_button;
}


void GameWidget::backbutton(){
   qDebug() << "back button pressed";
    emit backsignal();
}

void GameWidget::newbutton(){
   qDebug() << "new button pressed";
   newgame();
}

void GameWidget::newgame(){
    int i, j;
    for (i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            table_state[i][j] = 2;
            game_button[i][j]->setText("");
        }
    }
    turn = Xturn;
    if (turn == 0){
        turn_text->setText("noughts turn");
    }else{
        turn_text->setText("crosses turn");
    }
}

void GameWidget::gamebutton(){
   int x, y;
   QString turn_str;

   x = game_table->currentRow();
   y = game_table->currentColumn();

   qDebug() << "game button pressed x:"<<x<<" y:"<<y;

   if (table_state[x][y] == 2){
       qDebug() << "state is empty turn:"<<turn;
       if (turn == 0){
           table_state[x][y] = 0;
           game_button[x][y]->setText("O");
           turn_str = "noughts ";
       }else{
           table_state[x][y] = 1;
           game_button[x][y]->setText("X");
           turn_str = "crosses ";
       }

       winnercheck(x, y);

       switch(turn)
       {
           case Oturn:
                turn_text->setText("crosses turn");
                turn = Xturn;
                break;
           case Xturn:
                turn_text->setText("noughts turn");
                turn = Oturn;
                break;
            case win:
                turn_text->setText(turn_str + " won!");
                break;
            case draw:
                turn_text->setText("it's a draw!");
                break;

        }
    }
}

void GameWidget::winnercheck(int x, int y){
    int i, j, tmpx, tmpy;
    qDebug() << "check start";

    for(i = 0; i < 3; i++){
        tmpx = x + (i-1);

        if (tmpx < 0){
            continue;
        }
        for(j = 0; j < 3; j++){
            tmpy = y + (j-1);

            if (tmpy < 0){
                continue;
            }

            if (tmpx == x && tmpy == y){
                continue;
            }

            if (table_state[tmpx][tmpy] == table_state[x][y]){
                qDebug()<<"found match "<<tmpx<<tmpy;
                tmpx = tmpx + (i-1);
                tmpy = tmpy + (j-1);
                if (tmpx < 0 || tmpy < 0){
                    continue;
                }
                if (table_state[tmpx][tmpy] == table_state[x][y]){
                    qDebug()<<"found second match "<<tmpx<<tmpy;
                    turn = win;
                }
            }
        }
    }
    qDebug() << "check finish";
}
