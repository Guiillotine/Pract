#include "mainwindow.h"
#include "ui_mainwindow.h"
int f = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{            
    ui->setupUi(this);
    ui->label->installEventFilter(this);                        // Для перехвата событий (для клика по label)
    point = new QPoint(ui->label->width()/2,ui->label->height()/2); // Координаты центра label
    timer = new QTimer(this);                                   // Таймер для замера времени от одного нажатия клавиши до следующего
    connect(timer, SIGNAL(timeout()),this, SLOT(timerCheck())); // Связать таймер с остановкой проигрывания звука бега
    timer->start(100);                                          // Частота срабатывания - каждые 100 мс
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label)
    {
        if (event->type() == QEvent::MouseButtonPress)    // Если зажата кнопка мыши,
            f = 1;                                        // то в режим перетаскивания label
        else
        if (event->type() == QEvent::MouseButtonRelease)  // Если кнопка мыши отпущена,
            f = 0;                                        // то завершить перетаскивание
    }
    return false;
}

void MainWindow::timerCheck()
{
    if(f) ui->label->move((ui->label->parentWidget()->mapFromGlobal(QCursor::pos()))-(*point));
}
