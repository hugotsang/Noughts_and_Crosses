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

private:
    QPushButton *back_button;

};

#endif // GAMEWIDGET_H
