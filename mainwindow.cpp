#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "classroom.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bCont->hide();
    mainTimer = new QTimer(this);                                  // Главный таймер
    timerDrag = new QTimer(this);                                  // Таймер для замера времени от одного нажатия клавиши до следующего
    timer2 = new QTimer(this);                                     // Таймер для анимации перед началом урока (учитель входит в класс)
    connect(timer2, SIGNAL(timeout()),this, SLOT(tcherGoes()));  // Связать таймер 2 со слотом
    time = new QTime(0,0,0);
    //************Картинки*************
    icon.addFile(":/images/icon.ico");blank.addFile(":/images/Blank.ico");
    crossOn.load(":/images/crossGr.png");crossOff.load(":/images/cross.png");
    desk1.load(":/images/deskOne.png");desk2.load(":/images/desk.png");
    bkgndOp.load(":/images/classmOp.png"); bkgndCl.load(":/images/classCl.png");
    menu.load(":/images/classm.png");menu1.load(":/images/menu1.png");menu2.load(":/images/menu2.png");menuDel.load(":/images/delete.png");
    tcherSits.load(":/images/teatcherSits.png");
    tcher1.load(":/images/teatcher3-1.png");tcher2.load(":/images/teatcher3-2.png");tcher3.load(":/images/teatcher3-3.png");
    tcher4.load(":/images/teatcher3-4.png");tcher5.load(":/images/teatcher3-5.png");tcher6.load(":/images/teatcher3-6.png");
    //*************Звуки***************
    // Звонок
    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/sounds/call.wav"));
    //m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    //
    scrollArea = new QScrollArea();                    // Полосы прокрутки при уменьшении размеров окна
    scrollArea->setWindowIcon(icon);
    this->setGeometry(0,0,menu.width(),menu.height());      // Задать размеры окна размерами изображения
    point1 = new QPoint(menu1.width()/2,menu1.height()/2);  // Координаты центра labMenu1
    point2 = new QPoint(menu2.width()/2,menu2.height()/2);  // Координаты центра labMenu2
    pointDel = new QPoint(menuDel.width()/2,menuDel.height()/2);  // Координаты центра pointDel
    //***********Задний фон*************
    menu = menu.scaled(this->size(), Qt::KeepAspectRatio);  // Масштабирование изображения по высоте окна, с сохранением ширины изображения
    palette.setBrush(QPalette::Background, menu);
    this->setPalette(palette);
    //*************Labels***************
    // Учитель
    labTcher = new QLabel(this);
    labTcher->setPixmap(tcher1);
    labTcher->setGeometry(590,150,tcher1.width(),tcher1.height());
    labTcher->hide();
    // Заполнение класса местами для парт
    labels = new QLabel[15];     // Места для парт
    for (int i = 0, j = 0, k = 0; k<15; i++, k++)
    {
        if (i == 3) {i = 0; j++;}
        (labels+k)->setParent(this);
        (labels+k)->setPixmap(crossOff);      // Изначально на месте парты - крестик
        (labels+k)->setGeometry(180+i*160,320+j*100,31,31);
        (labels+k)->installEventFilter(this); // Для перехвата событий для каждой из парт
        (labels+k)->show();
    }
    // Счётчик кол-ва доступных для размещения парт
    labCounter = new QLabel(this);
    labCounter->setFont(QFont("Franklin Gothic Demi Cond", 20));
    labCounter->setStyleSheet("QLabel {color: #ddc6af;}");
    labCounter->setGeometry(815,645,60,20);
    labCounter->setText("x15");
    // Значок удаления в меню
    labDelete = new QLabel(this);
    labDelete->installEventFilter(this);                // Для перехвата событий для labDelete
    labDelete->setPixmap(menuDel);
    labDelete->setGeometry(800,150,menuDel.width(),menuDel.height());
    // Варианты парт в меню - одноместная и двухместная
    labMenu1 = new QLabel(this);
    labMenu1->installEventFilter(this);                // Для перехвата событий для labMenu1
    labMenu1->setPixmap(menu1);
    labMenu1->setGeometry(778,440,menu1.width(),menu1.height());
    labMenu2 = new QLabel(this);
    labMenu2->installEventFilter(this);                // Для перехвата событий для labMenu1
    labMenu2->setPixmap(menu2);
    labMenu2->setGeometry(750,270,menu2.width(),menu2.height());
    // Выпадающий список с предметами
    cmbbox = new QComboBox(this);
    cmbbox->setGeometry(765,6,135,20);
    cmbbox->addItem("Математика");cmbbox->addItem("Русский");cmbbox->addItem("История");cmbbox->addItem("Химия");
    //************Buttons**************
    // Начать урок
    bCont = new QPushButton(this);
    bCont->setGeometry(QRect(QPoint(720, 730),QSize(221, 65)));  // Размер и расположение кнопки
    bCont->setFont(QFont("Franklin Gothic Demi Cond", 20));      // Установить шрифт кнопки
    bCont->setStyleSheet("QPushButton {background-color: #ffeb7c; color: #d5950b;}");
    bCont->setText("Начать урок");
    bCont->show();
    connect(bCont, SIGNAL (clicked()),this, SLOT (BeginLsn()));
    // Удалить все парты
    bDel = new QPushButton(this);
    bDel->setGeometry(QRect(QPoint(720, 796),QSize(221, 65)));   // Размер и расположение кнопки
    bDel->setFont(QFont("Franklin Gothic Demi Cond", 20));       // Установить шрифт кнопки
    bDel->setStyleSheet("QPushButton {background-color: #ffeb7c; color: #d5950b;}");
    bDel->setText("Сброс");
    bDel->show();
    connect(bDel, SIGNAL (clicked()),this, SLOT (on_bDel_clicked()));
    // Выход
    bExit = new QPushButton(this);
    bExit->setGeometry(QRect(QPoint(720, 862),QSize(221, 65)));  // Размер и расположение кнопки
    bExit->setFont(QFont("Franklin Gothic Demi Cond", 20));       // Установить шрифт кнопки
    bExit->setStyleSheet("QPushButton {background-color: #ffeb7c; color: #d5950b;}");
    bExit->setText("Выход");
    bExit->show();
    connect(bExit, SIGNAL (clicked()),this, SLOT (on_bExit_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete[] labels; // Освобождение памяти от массива
    delete labMenu1; delete labMenu2; delete labCounter;
    delete labTcher;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{

    /*for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
        {
            if (i == 3) {i = 0; j++;}
            if((watched == labels+k)&&(event->type() == QEvent::MouseButtonPress))
                if (classRoom.GetPlan(i+1,j+1) == 1)
                {
                    classRoom.EditPlan(i+1,j+1,0); // Обозначить в плане отсутствие парты в i+1-вом ряду на j+1-вом месте
                    EditClass(i+1,j+1);
                    watched = labMenu1;
                }
        }*/

    if(watched == labDelete)
    {
        if (event->type() == QEvent::MouseButtonPress)     // Если зажата кнопка мыши
        {
            disconnect(timerDrag, nullptr, nullptr, nullptr);                          // Разорвать связь с предыдущими слотами
            connect(timerDrag, &QTimer::timeout, [=]() {Dragging(labDelete, pointDel);}); // Связать таймер с функцией с аргументами одноместной парты
            timerDrag->start(100);                                                     // Начать перетаскивание label мышью
        }
        else
        if (event->type() == QEvent::MouseButtonRelease)   // Если кнопка мыши отпущена,
        {
            timerDrag->stop();                             // то завершить перетаскивание
            // Проверка места, на котором отпущена мышь: если на каком-либо свободном крестике
            for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if (labDelete->x()<(labels+k)->x()+50 && labDelete->x()>(labels+k)->x()-75 && labDelete->y()<(labels+k)->y()+25 && labDelete->y()>(labels+k)->y()-75 && (classRoom->GetPlan(i+1,j+1) != 0))
                {
                    classRoom->EditPlan(i+1,j+1,0); // Обозначить в плане одноместную парту в i+1-вом ряду на j+1-вом месте
                    EditClass(i+1,j+1);
                    (labels+k)->setPixmap(crossOff);
                }
            }
            labDelete->setGeometry(800,150,menuDel.width(),menuDel.height());
        }
    }

    if(watched == labMenu1) // Если действие совершается над одноместной партой
    {
        if (event->type() == QEvent::MouseButtonPress)     // Если зажата кнопка мыши
        {
            disconnect(timerDrag, nullptr, nullptr, nullptr);                          // Разорвать связь с предыдущими слотами
            connect(timerDrag, &QTimer::timeout, [=]() {Dragging(labMenu1, point1);}); // Связать таймер с функцией с аргументами одноместной парты
            timerDrag->start(100);                                                     // Начать перетаскивание label мышью
        }
        else
        if (event->type() == QEvent::MouseButtonRelease)   // Если кнопка мыши отпущена,
        {
            timerDrag->stop();                             // то завершить перетаскивание
            // Проверка места, на котором отпущена мышь: если на каком-либо свободном крестике
            for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if (labMenu1->x()<(labels+k)->x()+25 && labMenu1->x()>(labels+k)->x()-75 && labMenu1->y()<(labels+k)->y()+25 && labMenu1->y()>(labels+k)->y()-75 && (classRoom->GetPlan(i+1,j+1) == 0))
                {
                    classRoom->EditPlan(i+1,j+1,1); // Обозначить в плане одноместную парту в i+1-вом ряду на j+1-вом месте
                    EditClass(i+1,j+1);
                }
            }
            labMenu1->setGeometry(778,440,menu1.width(),menu1.height());
        }
    }
    else if(watched == labMenu2) // Если действие совершается над двухместной партой
        {
            if (event->type() == QEvent::MouseButtonPress)     // Если зажата кнопка мыши
            {
                disconnect(timerDrag, nullptr, nullptr, nullptr); // Разорвать связь с предыдущими слотами
                connect(timerDrag, &QTimer::timeout, [=]() {Dragging(labMenu2, point2);});// Связать таймер с функцией с аргументами двухместной парты
                timerDrag->start(100);                                                    // Начать перетаскивание label мышью
            }
            else
            if (event->type() == QEvent::MouseButtonRelease)   // Если кнопка мыши отпущена,
            {
                timerDrag->stop();                             // то завершить перетаскивание
                // Проверка места, на котором отпущена мышь: если на каком-либо свободном крестике
                for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
                {
                    if (i == 3) {i = 0; j++;}
                    if (labMenu2->x()<(labels+k)->x()+25 && labMenu2->x()>(labels+k)->x()-130 && labMenu2->y()<(labels+k)->y()+25 && labMenu2->y()>(labels+k)->y()-75 && (classRoom->GetPlan(i+1,j+1) == 0))
                    {
                        classRoom->EditPlan(i+1,j+1,2); // Обозначить в плане одноместную парту в i+1-вом ряду на j+1-вом месте
                        EditClass(i+1,j+1);
                    }
                }
                labMenu2->setGeometry(750,270,menu2.width(),menu2.height());
            }
        }

    for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if((watched == labels+k)&&(event->type() == QEvent::MouseButtonDblClick)&&(classRoom->GetPlan(i+1,j+1) != 0))
                {
                    if (classRoom->GetPlan(i+1,j+1) == 1)
                    {
                        StudentWin1 *studentWin1 = new StudentWin1();
                        disconnect(this, &MainWindow::sig, nullptr, nullptr);              // Оборвать предыдущие связи сигнала
                        connect(this, &MainWindow::sig,studentWin1, &StudentWin1::FillWin);// Связать сигнал с новым слотом
                        emit sig(classRoom,k);
                        studentWin1->setModal(true); // Сделать окно модальным (появляющимся поверх основного и блокирующим его)
                        studentWin1->exec();
                        //labMenu1->setText(QString::number(classRoom->getStConcentr(k*2)));
                    }
                    else if (classRoom->GetPlan(i+1,j+1) == 2)
                    {
                        studentwin2 *studentWin2 = new studentwin2();
                        disconnect(this, &MainWindow::sig, nullptr, nullptr);              // Оборвать предыдущие связи сигнала
                        connect(this, &MainWindow::sig,studentWin2, &studentwin2::FillWin);// Связать сигнал с новым слотом
                        emit sig(classRoom,k);
                        studentWin2->setModal(true); // Сделать окно модальным (появляющимся поверх основного и блокирующим его)
                        studentWin2->exec();
                    }
                }
            }

    return false;
}

void MainWindow::EditClass(int row, int number)
{
    if (classRoom->GetPlan(row,number) == 1) // Если в плане одноместная парта, то отобразить на экране одноместную парту
    {
        (labels+(row-1)+(number-1)*3)->setGeometry((labels+(row-1)+(number-1)*3)->x()-50,(labels+(row-1)+(number-1)*3)->y()-15,desk1.width(),desk1.height());
        (labels+(row-1)+(number-1)*3)->setPixmap(desk1);
        AddToCounter(-1); // Уменьшить счётчик на экране
    }
    else if (classRoom->GetPlan(row,number) == 2) // Если в плане двухместная парта, то отобразить на экране двухместную парту
    {
        (labels+(row-1)+(number-1)*3)->setGeometry((labels+(row-1)+(number-1)*3)->x()-50,(labels+(row-1)+(number-1)*3)->y()-15,desk2.width(),desk2.height());
        (labels+(row-1)+(number-1)*3)->setPixmap(desk2);
        AddToCounter(-1); // Уменьшить счётчик на экране
    }
    else if (classRoom->GetPlan(row,number) == 0) // Если в плане нет парты, то отобразить на экране крестик
    {
        (labels+(row-1)+(number-1)*3)->setGeometry((labels+(row-1)+(number-1)*3)->x()+50,(labels+(row-1)+(number-1)*3)->y()+15,crossOn.width(),crossOn.height());
        (labels+(row-1)+(number-1)*3)->setPixmap(crossOn);
        AddToCounter(1); // Увеличить счётчик на экране
    }
}

// Перетаскивание мышью одной из парт меню
void MainWindow::Dragging(QLabel *lab, QPoint *point)
{   
    lab->move((lab->parentWidget()->mapFromGlobal(QCursor::pos()))-(*point));      // Передвигать lab вместе с курсором
    if (lab != labDelete) // Если взята не стирательная резинка, то подсвечивать доступные места для размещения парт
    for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
    {
        if (i == 3) {i = 0; j++;}
        if (lab->x()<(labels+k)->x()+25 && lab->x()>(labels+k)->x()-130 && lab->y()<(labels+k)->y()+25 && lab->y()>(labels+k)->y()-75)
            {
            if (classRoom->GetPlan(i+1,j+1) == 0)
                (labels+k)->setPixmap(crossOn);
            }
        else if (classRoom->GetPlan(i+1,j+1) == 0) (labels+k)->setPixmap(crossOff); // Вернуть неактивный крест, если на данном месте не стоит парты
    }
}

// Увеличение счётчика доступных для размещения парт на a
void MainWindow::AddToCounter(int a)
{
    QString s1 = labCounter->text();
    s1.remove(0,1); // Удалить символ "х" (от 0 до 1 символов строки)
    QString s = "x" + QString::number(s1.toInt() + a);
    labCounter->setText(s);
}


// Учитель заходит в класс
void MainWindow::tcherGoes()
{
    static int frame = 1, x = labTcher->x(), f = 0;
    if ((time->elapsed() >= 1000)&&(time->elapsed() <= 2000))
    {
        labTcher->show();
        palette.setBrush(QPalette::Background, bkgndOp);
        this->setPalette(palette);
        labTcher->show();
        f = 1;
    }
    if ((time->elapsed() > 2000)&&(time->elapsed() <= 2500))
    {
        palette.setBrush(QPalette::Background, menu);
        this->setPalette(palette);
    }
if(f)
{
    switch (frame)
    {
        case 1: labTcher->setPixmap(tcher1);
                break;
        case 2: labTcher->setPixmap(tcher2);
                break;
        case 3: labTcher->setPixmap(tcher3);
                break;
        case 4: labTcher->setPixmap(tcher4);
                break;
        case 5: labTcher->setPixmap(tcher5);
                break;
        case 6: labTcher->setPixmap(tcher6);
                break;
    }
    frame++;
    if (frame == 7) frame = 1;
    labTcher->setGeometry(x,150,tcher1.width(),tcher1.height());
    x-=5;
    if (x == 350)
    {
        labTcher->setPixmap(tcherSits);
        labTcher->setGeometry(343,157,tcherSits.width(),tcherSits.height());
        timer2->stop(); // Отключение таймера по достижении объектом нужной точки на экране
    }
}
}

void MainWindow::BeginLsn()
{
    labMenu1->hide();
    labMenu2->hide();
    labDelete->hide();
    labCounter->hide();
    cmbbox->hide();
    bCont->hide();
    bDel->hide();
    bExit->hide();
    for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if (classRoom->GetPlan(i+1,j+1) == 0)
                    (labels+k)->clear(); // Убрать крестики, оставить только парты
            }
    m_player->play();
    time->start();                    // Начать отсчет времени
    timer2->start(100);
}

void MainWindow::on_bDel_clicked()
{
     QMessageBox msgBox;
     msgBox.setWindowTitle(" ");
     msgBox.setIcon(QMessageBox::Warning);
     QAbstractButton *yes = msgBox.addButton("Да",QMessageBox::YesRole);
     QAbstractButton *no = msgBox.addButton("Нет",QMessageBox::NoRole);
     msgBox.setText("Вы уверены?");
     msgBox.setWindowIcon(blank);
     msgBox.exec();
     if(msgBox.clickedButton() == yes) DeleteAllDesks();
     else if(msgBox.clickedButton() == no)  msgBox.close();
}

void MainWindow::on_bExit_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(" ");
    msgBox.setIcon(QMessageBox::Warning);
    QAbstractButton *yes = msgBox.addButton("Да",QMessageBox::YesRole);
    QAbstractButton *no = msgBox.addButton("Нет",QMessageBox::NoRole);
    msgBox.setText("Завершить работу программы?");
    msgBox.setWindowIcon(blank);
    msgBox.exec();
    if(msgBox.clickedButton() == yes) {scrollArea->close();}
    else if(msgBox.clickedButton() == no)  msgBox.close();
}

void MainWindow::DeleteAllDesks()
{
    for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if (classRoom->GetPlan(i+1,j+1) != 0)
                {
                    classRoom->EditPlan(i+1,j+1,0);  // Обозначить в плане отсутствие парты в i+1-вом ряду на j+1-вом месте
                    EditClass(i+1,j+1);             // Убрать парту с экрана
                    (labels+k)->setPixmap(crossOff);
                }
            }
}








// Перетаскивание
/*bool MainWindow::eventFilter(QObject *watched, QEvent *event)
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
*/
