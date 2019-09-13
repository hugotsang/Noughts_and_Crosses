#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtWidgets>

/*Class name: GameWidget                        */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Set declarations for GameWidget  */
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
    QHBoxLayout *score_container[2];
    QLabel *icon_img[2];
    QPixmap *icon_pixmap[2];
    QString score_str[2];
    QLabel *score_text[2];
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

/*Class name: TableDelegate                     */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Draws grid for game table        */
class TableDelegate : public QItemDelegate {

  public:
    TableDelegate( QObject *parent ) : QItemDelegate( parent ) { }
    //Replaces default paint event
    void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const {
      QItemDelegate::paint( painter, option, index ); //calls default paint event so that itcan be edited
      painter->fillRect(option.rect, QColor(49, 49, 49));
      QPen pen;
      pen.setColor("#efefefef");
      pen.setWidth(3);
      painter->setPen(pen);
      painter->drawLine(QLine(0, 120, 360, 120));
      painter->drawLine(QLine(0, 240, 360, 240));
      painter->drawLine(QLine(120, 0, 120, 360));
      painter->drawLine(QLine(240, 0, 240, 360));
    }
};
#endif // GAMEWIDGET_H
