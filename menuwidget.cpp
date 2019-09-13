#include "mainwindow.h"
#include "menuwidget.h"

/*Function name: MenuWidget(QWidget *parent)    */
/*Parameter: QWidget *parent                    */
/*Return: None                                  */
/*Description: Create an instance of menu widget*/
MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent)
{
    title = new QLabel(this);
    title->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    title->setText("<span style = \"color: #f08113;\"> noughts </span>"
                   "<span style = \"color: #ffffff;\">+</span>"
                   "<span style = \"color: #b8398e;\"> crosses</span>");
    title->setAlignment(Qt::AlignHCenter);
    title->setStyleSheet("background-color: #313131;"
                         "border: 0px;"
                         "font: Roboto Condensed Regular, Arial;"
                         "font-size: 58px;"
                         "padding-top: 270px;");


    QPixmap *O_img = new QPixmap(":/assets/assets/nought-01.png");
    QPixmap *X_img = new QPixmap(":/assets/assets/cross-01.png");
    QPixmap *img_pixmap = new QPixmap(146, 80);

    //draw icon and sepearator line
    img_pixmap->fill(Qt::transparent);
    QPainter *painter = new QPainter(img_pixmap);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->drawPixmap(0, 17, 46, 46, O_img->scaled(46, 46, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    QPen pen;
    pen.setColor("#ffffff");
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLine(75, 0, 75, 80);
    painter->drawPixmap(100, 17, 46, 46, X_img->scaled(46, 46, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter->end();

    title_img = new QLabel(this);
    title_img->setPixmap(*img_pixmap);
    title_img->setAlignment(Qt::AlignHCenter);

    start_button = new QPushButton("Start Game", this);
    start_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    start_button->setFixedSize(248, 62);
    start_button->setStyleSheet("background-color: #efefef;"
                                "border:0px;"
                                "border-radius: 31px;"
                                "color: #313131;"
                                "font: Roboto Bold, Roboto Condensed Regular,  Arial Bold;"
                                "font-size: 18px;");

    connect(start_button, SIGNAL(released()),this , SLOT(startbutton()));

    QGridLayout *menulayout = new QGridLayout;
    menulayout->addWidget(title,0,0);
    menulayout->addWidget(title_img,1,0);
    menulayout->addWidget(start_button,2,0);
    menulayout->setAlignment(start_button, Qt::AlignHCenter);
    menulayout->setRowMinimumHeight(3, 78);
    setLayout(menulayout);
}

/*Function name: ~MenuWidget()                  */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Destructor for MenuWidget        */
MenuWidget::~MenuWidget()
{
    delete title;
    delete start_button;
}

/*Function name: startbutton()                  */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Emits a signal to switch widget  */
void MenuWidget::startbutton(){
   qDebug() << "Start button pressed";
    emit startsignal();

}
