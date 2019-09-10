#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtWidgets>


class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

signals:
    void backsignal();

private slots:
    void backbutton();
    void gamebutton();
    void newbutton();

private:
    QPushButton *back_button;
    QPushButton *new_button;
    QPushButton *game_button[3][3];
    int table_state[3][3];
    QTableWidget *game_table;
    QLabel *score_text;
    int score[2];
    QLabel *turn_text;
    enum turnT{
        Oturn,
        Xturn,
        win,
        draw
    };
    turnT turn;
    int turnnum;
    void winnercheck(int x, int y);
    void newgame();
};

#endif // GAMEWIDGET_H
