#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QStackedWidget>
#include <QGraphicsView>
//QScrollArea *scrollArea;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    MainWindow *w = new MainWindow();
    QPixmap bkgrnd = QPixmap(":/images/classm.png");
    w->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);    // Вертикальная полоса присутствует всегда
    w->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Убрать горизонтальную полосу прокрутки
    w->scrollArea->setWidget(w); // Прокручиваемый виджет - окно (и соответственно его содержимое)
    w->scrollArea->setFixedWidth(bkgrnd.width()+20);                  // Изменение размера окна по Х запрещено, раз-р по Х - раз-р фонового изобр-я + ширина полосы прокрутки
    w->scrollArea->setMaximumSize(bkgrnd.width()+20,bkgrnd.height()); // Рраз-р по Y - от 200 pix до раз-ра фонового изобр.
    w->scrollArea->resize(bkgrnd.width()+20,bkgrnd.height());         // Открывать окно в максимально допустимом размере
    w->scrollArea->show();
    //w->show();
    return a.exec();
}
