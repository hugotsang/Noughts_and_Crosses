#include "mainwindow.h"
#include "gamewidget.h"

/*Function name: GameWidget(QWidget *parent)    */
/*Parameter: QWidget *parent                    */
/*Return: None                                  */
/*Description: Create an instance of game widget*/
GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent)
{
    int i, j;

    turn = Xturn;
    turnnum = 0;

    score[0] = 0;
    score[1] = 0;
    score_text = new QLabel(this);
    score_text->setText("noughts score: " + QString::number(score[0]) + " crosses score: " + QString::number(score[1]));
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

/*Function name: ~GameWidget()                  */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Destructor for GameWidget        */
GameWidget::~GameWidget()
{
    delete game_table;
    delete back_button;
}

/*Function name: backbutton()                   */
/*Parameter: none                               */
/*Return: None                                  */
/*Description: Reset scores, game grid and send */
/*             signal to switch display widget  */
void GameWidget::backbutton(){
   qDebug() << "back button pressed";
   newgame();
   score[0] = 0;
   score[1] = 0;
   score_text->setText("noughts score: " + QString::number(score[0]) + " crosses score: " + QString::number(score[1]));
    emit backsignal();
}

/*Function name: newbutton()                    */
/*Parameter: none                               */
/*Return: None                                  */
/*Description: SLOT for new game button         */
void GameWidget::newbutton(){
   qDebug() << "new button pressed";
   newgame();
}

/*Function name: newgame()                      */
/*Parameter: none                               */
/*Return: None                                  */
/*Description: Reset scores, game grid          */
void GameWidget::newgame(){
    int i, j;
    for (i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            table_state[i][j] = 2;
            game_button[i][j]->setText("");
            game_button[i][j]->setEnabled(true);
        }
    }
    turnnum = 0;
    turn = Xturn;
    if (turn == 0){
        turn_text->setText("noughts turn");
    }else{
        turn_text->setText("crosses turn");
    }
}

/*Function name: gamebutton()                   */
/*Parameter: none                               */
/*Return: None                                  */
/*Description: Sets user inputs for game grid   */
void GameWidget::gamebutton(){
   int i, j, x, y;
   QString turn_str;

   turnnum++;
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
       qDebug() << "turnnum:"<<turnnum;
       if (turnnum == 9 && turn != win){
           turn = draw;
       }
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
                score[table_state[x][y]]++;
                turn_text->setText(turn_str + " won!");
                score_text->setText("noughts score: " + QString::number(score[0]) + " crosses score: " + QString::number(score[1]));
                for (i = 0; i < 3; i++){
                    for(j = 0; j < 3; j++){
                        game_button[i][j]->setEnabled(false);
                    }
                }
                break;
            case draw:
                turn_text->setText("it's a draw!");
                for (i = 0; i < 3; i++){
                    for(j = 0; j < 3; j++){
                        game_button[i][j]->setEnabled(false);
                    }
                }
                break;

        }
    }
}

/*Function name: winnercheck()                  */
/*Parameter: none                               */
/*Return: None                                  */
/*Description: Checks for winner                */
void GameWidget::winnercheck(int x, int y){
    int i, j, tmpx, tmpy;
    qDebug() << "check start";

    for(i = 0; i < 3; i++){
        tmpx = x + (i-1);

        if (tmpx < 0 || tmpx>=3){
            continue;
        }
        qDebug()<<"error match "<<tmpx<<tmpy;

        for(j = 0; j < 3; j++){
            tmpy = y + (j-1);

            if (tmpy < 0 || tmpy>=3|| tmpx>=3){
                continue;
            }

            if (tmpx == x && tmpy == y){
                continue;
            }

            if (table_state[tmpx][tmpy] == table_state[x][y]){
                qDebug()<<"found match "<<tmpx<<tmpy;
                tmpx = tmpx + (i-1);
                tmpy = tmpy + (j-1);
                if (tmpx < 3 && tmpy < 3 && tmpx>=0 && tmpy>=0){
                    if (table_state[tmpx][tmpy] == table_state[x][y]){
                        qDebug()<<"1found second match "<<tmpx<<tmpy;
                        turn = win;
                        break;
                    }
                }
                //checks other side for second match
                tmpx = x - (i-1);
                tmpy = y - (j-1);
                if (tmpx < 3 && tmpy < 3 && tmpx>=0 && tmpy>=0){
                    if (table_state[tmpx][tmpy] == table_state[x][y]){
                        qDebug()<<"2found second match "<<tmpx<<tmpy;
                        turn = win;
                        break;
                    }
                }else{
                    continue;
                }
            }
        }
    }
    qDebug() << "check finish";
}
