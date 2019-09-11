#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QtWidgets>


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
    QPixmap *img_pixmap;
    QPushButton *start_button;

};

#endif // MENUWIDGET_H
