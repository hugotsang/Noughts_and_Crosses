#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QtWidgets>

/*Class name: MenuWidget                        */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Set declarations for MenuWidget  */
class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);
    ~MenuWidget();

signals:
    void startsignal();

private slots:
    void startbutton();

private:
    QLabel *title;
    QLabel *title_img;
    QPushButton *start_button;

};

#endif // MENUWIDGET_H
