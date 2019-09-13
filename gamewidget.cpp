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

    score_str[0] = "noughts score: ";
    score_str[1] = "crosses score: ";

    icon_pixmap[0] = new QPixmap(":/assets/assets/nought-01.png");
    icon_pixmap[1] = new QPixmap(":/assets/assets/cross-01.png");
    QPixmap *img_pixmap = new QPixmap(23, 23);

    for (i = 0; i < 2; i++){
        score[i] = 0;
        score_text[i] = new QLabel(this);
        score_text[i]->setStyleSheet("border:0px;"
                                    "color: #efefef;"
                                    "font: Roboto Bold, Roboto Condensed Regular, Arial Bold;"
                                    "font-size: 21px;");
        score_text[i]->setAlignment(Qt::AlignHCenter);
        score_text[i]->setText( score_str[i] + QString::number(score[i]));

        //Draw icons for scores
        icon_img[i] = new QLabel(this);
        icon_img[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        icon_img[i]->setFixedSize(QSize(23,23));

        img_pixmap->fill(Qt::transparent);
        QPainter *painter = new QPainter(img_pixmap);
        painter->setRenderHint(QPainter::SmoothPixmapTransform);
        painter->drawPixmap(0, 0, 23, 23, icon_pixmap[i]->scaled(23, 23, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        painter->end();
        icon_img[i]->setPixmap(*img_pixmap);
        score_container[i] = new QHBoxLayout;
        score_container[i]->addWidget(icon_img[i]);
        score_container[i]->addWidget(score_text[i]);

    }

    turn_text = new QLabel(this);
    if (turn == 0){
        turn_text->setText("noughts turn!");
    }else{
        turn_text->setText("crosses turn!");
    }
    turn_text->setStyleSheet( "border: 0px;"
                              "color: #efefef;"
                              "font: Roboto Condensed Regular, Arial Bold;"
                              "font-size: 31px;");
    turn_text->setAlignment(Qt::AlignHCenter);

    game_table = new QTableWidget(3, 3, this);
    game_table->setItemDelegate(new TableDelegate(this));
    game_table->verticalHeader()->setVisible(false);
    game_table->horizontalHeader()->setVisible(false);
    game_table->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    game_table->setFixedSize(360, 360);
    game_table->setStyleSheet( "border: 0px;");
    game_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_table->setShowGrid(false);
    game_table->setFocusPolicy(Qt::NoFocus);
    for (i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            game_button[i][j] = new QPushButton(this);
            game_button[i][j]->setStyleSheet("border: 5px;");
//                                             "background-color: #313131;");
            game_table->setCellWidget(i, j, game_button[i][j]);

            table_state[i][j] = 2; // 2 is used for cell being empty
            connect(game_button[i][j], SIGNAL(released()), this, SLOT(gamebutton()));
            game_table->setColumnWidth(j, 120);
        }
        game_table->setRowHeight(i, 120);
    }

    new_button = new QPushButton("New game", this);
    new_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    new_button->setFixedSize(240, 62);
    new_button->setStyleSheet("background-color: #efefef;"
                              "border:0px;"
                              "border-radius: 31px;"
                              "color: #313131;"
                              "font: Roboto Bold, Roboto Condensed Regular, Arial Bold;"
                              "font-size: 18px;");
    connect(new_button, SIGNAL(released()), this, SLOT(newbutton()));

    back_button = new QPushButton("Back", this);
    back_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    back_button->setFixedSize(240, 62);
    back_button->setStyleSheet("background-color: #efefef;"
                               "border:0px;"
                               "border-radius: 31px;"
                               "color: #313131;"
                               "font: Roboto Bold, Roboto Condensed Regular, Arial Bold;"
                               "font-size: 18px;");
    connect(back_button, SIGNAL(released()), this, SLOT(backbutton()));

    //set layout for widgets
    QGridLayout *Gamelayout = new QGridLayout;
    Gamelayout->setRowMinimumHeight(0, 50);
    Gamelayout->addLayout(score_container[0], 1, 0);
    Gamelayout->addLayout(score_container[1], 1, 1);
    Gamelayout->addWidget(turn_text, 2, 0, 1, 2);
    Gamelayout->setAlignment(turn_text, Qt::AlignCenter);
    Gamelayout->setRowStretch(2, 1);
    Gamelayout->addWidget(game_table, 3, 0, 1, 2);
    Gamelayout->setAlignment(game_table, Qt::AlignHCenter);
    Gamelayout->setRowMinimumHeight(4, 33);
    Gamelayout->addWidget(back_button, 5, 0);
    Gamelayout->addWidget(new_button, 5, 1);
    Gamelayout->setRowMinimumHeight(6, 75);
    setLayout(Gamelayout);

}

/*Function name: ~GameWidget()                  */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Destructor for GameWidget        */
GameWidget::~GameWidget(){
    delete game_table;
    delete back_button;
}

/*Function name: backbutton()                   */
/*Parameter: none                               */
/*Return: None                                  */
/*Description: Reset scores, game grid and send */
/*             signal to switch display widget  */
void GameWidget::backbutton(){
    int i;
   qDebug() << "back button pressed";
   newgame();
   for (i = 0; i < 2; i++){
       score[i] = 0;
       score_text[i]->setText( score_str[i] + QString::number(score[i]));
   }
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
    if (turn == Oturn){
        turn = Xturn;
    }else if(turn == Xturn){
        turn = Oturn;
    }else{
        turn = Xturn;
        qDebug()<<"not x or o";
    }
    if (turn == 0){
        turn_text->setText("noughts turn!");
    }else{
        turn_text->setText("crosses turn!");
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
                turn_text->setText("crosses turn!");
                turn = Xturn;
                break;
           case Xturn:
                turn_text->setText("noughts turn!");
                turn = Oturn;
                break;
            case win:
           //using table_state[x][y] to find current player
                score[table_state[x][y]]++;
                turn_text->setText(turn_str + " won!");
                score_text[table_state[x][y]]->setText( score_str[table_state[x][y]] + QString::number(score[table_state[x][y]]));
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
            tmpx = x + (i-1);//second match changes tmpx value
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

                //checks second match is not same cell
                if(tmpx == x && tmpy == y){
                    continue;
                }

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
                }
            }
        }
        //if win break i loop
        if (turn == win){
            break;
        }
    }
    qDebug() << "check finish";
}

