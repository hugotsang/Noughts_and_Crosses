#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

/*Class name: MainWindow                        */
/*Parameter: None                               */
/*Return: None                                  */
/*Description: Set declarations for MainWindow  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void backsignal();

private:
    QStackedWidget *widgetstack;

private slots:
    void changewidget();
};

#endif // MAINWINDOW_H
