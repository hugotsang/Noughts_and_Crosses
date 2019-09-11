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
    score_text->setStyleSheet("border:0px;"
                              "color: #efefef;"
                              "font: Roboto Bold, Roboto Condensed Regular, Arial Bold;"
                              "font-size: 18px;");
    score_text->setAlignment(Qt::AlignHCenter);

    turn_text = new QLabel(this);
    if (turn == 0){
        turn_text->setText("noughts turn");
    }else{
        turn_text->setText("crosses turn");
    }
    turn_text->setStyleSheet( "border:0px;"
                              "color: #efefef;"
                              "font: Roboto Bold, Roboto Condensed Regular, Arial Bold;"
                              "font-size: 18px;");
    turn_text->setAlignment(Qt::AlignHCenter);

    game_table = new QTableWidget(3, 3, this);
    game_table->verticalHeader()->setVisible(false);
    game_table->horizontalHeader()->setVisible(false);
    for (i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            game_button[i][j] = new QPushButton(this);
            game_button[i][j]->setStyleSheet("border: 0px;"
                                             "background-color: #313131");
            game_table->setCellWidget(i, j, game_button[i][j]);
            table_state[i][j] = 2; // 2 is used for cell being empty
            connect(game_button[i][j], SIGNAL(released()), this, SLOT(gamebutton()));
            game_table->setRowHeight(j, 120);
        }
        game_table->setRowHeight(i, 120);
    }

    new_button = new QPushButton("New game", this);
    new_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    new_button->setFixedSize(248, 62);
    new_button->setStyleSheet("background-color: #efefef;"
                              "border:0px;"
                              "border-radius: 31px;"
                              "color: #313131;"
                              "font: Roboto Bold, Roboto Condensed Regular, Arial Bold;"
                              "font-size: 18px;");
    connect(new_button, SIGNAL(released()), this, SLOT(newbutton()));

    back_button = new QPushButton("Back", this);
    back_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    back_button->setFixedSize(248, 62);
    back_button->setStyleSheet("background-color: #efefef;"
                               "border:0px;"
                               "border-radius: 31px;"
                               "color: #313131;"
                               "font: Roboto Bold, Roboto Condensed Regular, Arial Bold;"
                               "font-size: 18px;");
    connect(back_button, SIGNAL(released()), this, SLOT(backbutton()));

    QGridLayout *Gamelayout = new QGridLayout;
    Gamelayout->addWidget(score_text, 0, 0, 1, 2);
    Gamelayout->addWidget(turn_text, 1, 0, 1, 2);
    Gamelayout->addWidget(game_table, 2, 0, 1, 2);
    Gamelayout->setAlignment(game_table, Qt::AlignHCenter);
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
            game_button[i][j]->setIcon(QIcon());
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

   x = game_table->currentRow();
   y = game_table->currentColumn();

   qDebug() << "game button pressed x:"<<x<<" y:"<<y;

   if (table_state[x][y] == 2){
       turnnum++; //add turn if valid move

       qDebug() << "state is empty turn:"<<turn;
       if (turn == 0){
           table_state[x][y] = 0;
           game_button[x][y]->setIcon(QPixmap(":/assets/assets/nought-01.png"));
           game_button[x][y]->setIconSize(QSize(64, 64));
           turn_str = "noughts ";
       }else{
           table_state[x][y] = 1;
           game_button[x][y]->setIcon(QPixmap(":/assets/assets/cross-01.png"));
           game_button[x][y]->setIconSize(QSize(64, 64));
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
