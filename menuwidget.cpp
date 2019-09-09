#include "mainwindow.h"
#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent)
{
    title = new QLabel(this);
    title->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    title->setText("noughts and crosses");
    title->setGeometry(10, 10, 200, 50);
    title->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    start_button = new QPushButton("Start Game", this);
    start_button->setGeometry(200, 320, 100, 62);
    connect(start_button, SIGNAL(released()),this , SLOT(startbutton()));

    QGridLayout *menulayout = new QGridLayout;
    menulayout->addWidget(title,0,0);
    menulayout->addWidget(start_button,1,0);
    setLayout(menulayout);



}

MenuWidget::~MenuWidget()
{
    delete title;
    delete start_button;
}


void MenuWidget::startbutton(){
   qDebug() << "Start button pressed";
    emit startsignal();

}
