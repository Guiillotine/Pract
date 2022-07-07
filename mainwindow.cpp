#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "classroom.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bCont->hide();
    timer = new QTimer();                                   // Секундомер для засечения времени урока
    timerLsn = new QTimer();                              // Для смены содержимого подсказок
    timerDrag = new QTimer();                               // Таймер для замера времени от одного нажатия клавиши до следующего
    timer2 = new QTimer();                                  // Таймер для анимации перед началом урока (учитель входит в класс)
    //connect(timer, SIGNAL(timeout()),this, SLOT(Stopwatch()));  // Связать таймер со слотом - секундомером
    connect(timerLsn, SIGNAL(timeout()),this, SLOT(DuringLsn()));  // Связать таймер со слотом
    connect(timer2, SIGNAL(timeout()),this, SLOT(tcherGoes()));  // Связать таймер 2 со слотом
    time = new QTime(0,0,0);
    //************Картинки**************
    icon.addFile(":/images/icon.ico");blank.addFile(":/images/Blank.ico");
    crossOn.load(":/images/crossGr.png");crossOff.load(":/images/cross.png");
    desk1.load(":/images/deskOne.png");desk2.load(":/images/desk.png");
    deskGG.load(":/images/deskgg.png");deskBB.load(":/images/deskbb.png");deskGB.load(":/images/deskgb.png");deskBG.load(":/images/deskbg.png");
    deskB.load(":/images/deskb.png");deskG.load(":/images/deskg.png");
    bkgndOp.load(":/images/classmOp.png"); bkgndCl.load(":/images/classCl.png");
    menu.load(":/images/classm.png");menu1.load(":/images/menu1.png");menu2.load(":/images/menu2.png");menuDel.load(":/images/delete.png");
    tcherSits.load(":/images/teatcherSits.png");tcherMenu.load(":/images/teatcherMenu.png");
    tcher1.load(":/images/teatcher3-1.png");tcher2.load(":/images/teatcher3-2.png");tcher3.load(":/images/teatcher3-3.png");
    tcher4.load(":/images/teatcher3-4.png");tcher5.load(":/images/teatcher3-5.png");tcher6.load(":/images/teatcher3-6.png");
    statKind.load(":/images/statKind.png");statNorm.load(":/images/statNorm.png");statEvil.load(":/images/statEvil.png");
    table.load(":/images/table.png");
    //*************Звуки***************
    // Звонок
    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("call2.wav"));
    //
    scrollArea = new QScrollArea();                    // Полосы прокрутки при уменьшении размеров окна
    scrollArea->setWindowIcon(icon);
    scrollArea->setWindowTitle("Моделирование поведения учеников в классе");
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
    labTcher = new MyLabel(this,tcherMenu);
    //labTcher->setPixmap(tcherMenu);
    //labTcher->setGeometry(342,155,tcherMenu.width(),tcherMenu.height());
    labTcher->installEventFilter(this); // Для перехвата событий для label учителя
    // Заполнение класса местами для парт
    labels = new QLabel[15];     // Места для парт
    for (int i = 0, j = 0, k = 0; k<15; i++, k++)
    {
        if (i == 3) {i = 0; j++;}
        (labels+k)->setParent(this);
        //(labels+k)->setPixmap(crossOff);      // Изначально на месте парты - крестик
        (labels+k)->setGeometry(180+i*160,320+j*100,31,31);
        (labels+k)->installEventFilter(this); // Для перехвата событий для каждой из парт
        (labels+k)->show();
    }
    // Выделение памяти под символы и текст, отображающие состояние учеников
    labSymbols = new QLabel[30];              // Символы - подсказки
    labLearn = new QLabel[30];                // Усвоение урока учениками
    labInterest = new QLabel[30];             // Интерес учеников
    labDiscip = new QLabel[30];               // Дисциплина учеников
    // Счётчик кол-ва доступных для размещения парт
    labCounter = new QLabel(this);
    labCounter->setFont(QFont("Franklin Gothic Demi Cond", 20));
    labCounter->setStyleSheet("QLabel {color: #ddc6af;}");
    labCounter->setGeometry(815,645,60,20);
    labCounter->setText("x15");
    // Значок удаления в меню
    labDelete = new MyLabel(this,menuDel);
    labDelete->installEventFilter(this);               // Для перехвата событий для labDelete
    labDelete->setPos(800,150);
    // Варианты парт в меню - одноместная и двухместная
    labMenu1 = new MyLabel(this,menu1);
    labMenu1->installEventFilter(this);                // Для перехвата событий для labMenu1
    labMenu1->setPos(778,440);
    labMenu2 = new MyLabel(this,menu2);
    labMenu2->installEventFilter(this);                // Для перехвата событий для labMenu2
    labMenu2->setPos(750,270);
    // Секундомер
    labMinutes = new QLabel(this);
    labMinutes->setGeometry(802,40,80,40);
    labMinutes->setFont(QFont("Franklin Gothic Demi Cond", 20));
    labMinutes->setStyleSheet("QLabel {color: #ddc6af;}");
    labMinutes->setText("00");
    labSeconds = new QLabel(this);
    labSeconds->setGeometry(830,40,80,40);
    labSeconds->setFont(QFont("Franklin Gothic Demi Cond", 20));
    labSeconds->setStyleSheet("QLabel {color: #ddc6af;}");
    labSeconds->setText(":00");
    labStWtch = new QLabel(this);
    labStWtch->setGeometry(767,10,250,40);
    labStWtch->setFont(QFont("Franklin Gothic Demi Cond", 20));
    labStWtch->setStyleSheet("QLabel {color: #ddc6af;}");
    labStWtch->setText("Время урока");
    // Школьная доска
    labBoard = new QLabel(this);
    labBoard->setGeometry(305,0,300,100);
    // Таблица с подсказками
    labTab = new MyLabel(this,table);
    labTab->setPos(753,310);
    //*********************************
    // Выпадающий список с предметами
    cmbbox = new QComboBox(this);
    cmbbox->setGeometry(765,6,135,20);
    // Считать из класса предметов названия для ComboBox
    for (int i = 0; i < classRoom->subject->getSbjNmbr(); i++)
        cmbbox->addItem(classRoom->subject->getSubject(i));
    //************Buttons**************
    // Начать урок
    bCont = new MyButton(this,"Начать урок");
    bCont->SetPos(720, 730);
    connect(bCont, SIGNAL (clicked()),this, SLOT (BeginLsn()));
    // Удалить все парты
    bDel = new MyButton(this,"Сброс");
    bDel->SetPos(720, 796);
    connect(bDel, SIGNAL (clicked()),this, SLOT (on_bDel_clicked()));
    // Выход
    bExit = new MyButton(this,"Выход");
    bExit->SetPos(720, 862);
    connect(bExit, SIGNAL (clicked()),this, SLOT (on_bExit_clicked()));
    // Редактировать
    bPause = new MyButton(this,"Редактировать");
    bPause->SetPos(720, 796);
    connect(bPause, SIGNAL (clicked()),this, SLOT (Pause()));
    // Закончить урок
    bFinLsn = new MyButton(this,"Закончить урок");
    bFinLsn->SetPos(720, 862);
    connect(bFinLsn, SIGNAL (clicked()),this, SLOT (on_bFinLsn_clicked()));
    //*******Секундомер*********
    stwtch = new Stopwatch(timer,labMinutes,labSeconds); // Секундомер
    connect(timer, &QTimer::timeout, [=]() {LessonTime();});
    // Вид экрана до начала урока
    BfrLsn();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete[] labels; // Освобождение памяти от массива
    delete[] labSymbols;
    delete labMenu1; delete labMenu2; delete labCounter;
    delete labMinutes; delete labSeconds; delete labStWtch;
    delete labLearn; delete labInterest; delete labDiscip;
    delete labCounter;
    delete labTcher;
    delete labBoard;
    delete timer;delete timerDrag;delete timer2;delete timerLsn;
    delete point1;delete point2;delete pointDel;
    delete stwtch;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
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
            // Проверка места, на котором отпущена мышь
            for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if (labDelete->x()<(labels+k)->x()+50 && labDelete->x()>(labels+k)->x()-75 && labDelete->y()<(labels+k)->y()+25 && labDelete->y()>(labels+k)->y()-75 && (classRoom->GetPlan(i+1,j+1) != 0))
                {
                    classRoom->students[k*2].DelSt();         // Удалить данные ученика
                    if (classRoom->GetPlan(i+1,j+1) == 2) classRoom->students[k*2+1].DelSt(); // Удалить данные ученика-соседа
                    classRoom->EditPlan(i+1,j+1,0); // Удалить парту из плана
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
if (!timer->isActive()) //Разреш. редактирование данные если урок не начался или стоит на паузе
{
    if((watched == labTcher)&&(event->type() == QEvent::MouseButtonDblClick))
    {// Окрыть окно ввода данных учителя
          TeacherWin *tchrWin = new TeacherWin();
          connect(this, &MainWindow::sigTcher,tchrWin, &TeacherWin::FillWin);
          emit sigTcher(classRoom);
          tchrWin->setModal(true); // Сделать окно модальным (появляющимся поверх основного и блокирующим его)
          tchrWin->exec();
    }

    for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if((watched == labels+k)&&(event->type() == QEvent::MouseButtonDblClick)&&(classRoom->GetPlan(i+1,j+1) != 0))
                {
                    if (classRoom->GetPlan(i+1,j+1) == 1)
                    {  // Окрыть окно ввода данных ученика для одноместной парты
                        StudentWin1 *studentWin1 = new StudentWin1();
                        disconnect(this, &MainWindow::sig, nullptr, nullptr);              // Оборвать предыдущие связи сигнала
                        connect(this, &MainWindow::sig,studentWin1, &StudentWin1::FillWin);// Связать сигнал с новым слотом
                        emit sig(classRoom,k);
                        studentWin1->setModal(true); // Сделать окно модальным (появляющимся поверх основного и блокирующим его)
                        studentWin1->exec();
                        Show1deskLab(k);
                    }
                    else if (classRoom->GetPlan(i+1,j+1) == 2)
                    {  // Окрыть окно ввода данных ученика для двухместной парты
                        studentwin2 *studentWin2 = new studentwin2();
                        disconnect(this, &MainWindow::sig, nullptr, nullptr);              // Оборвать предыдущие связи сигнала
                        connect(this, &MainWindow::sig,studentWin2, &studentwin2::FillWin);// Связать сигнал с новым слотом
                        emit sig(classRoom,k);
                        studentWin2->setModal(true); // Сделать окно модальным (появляющимся поверх основного и блокирующим его)
                        studentWin2->exec();
                        Show2deskLab(k);
                    }
                    if((classRoom->GetPlan(i+1,j+1) != 0)&&(classRoom->getBuffStNum()!= -1))
                    {
                        // Проверить пол ученика с номером из буфера (обновить картинку на случай, если уч. поменялись местами)
                        int buffStNum = classRoom->getBuffStNum();// Номер ученика из буффера
                        if (classRoom->GetPlan((buffStNum/2)%3+1,(buffStNum/6)+1) == 1)// В буф-ре есть д-е ученика и он сидел за одномест.п.
                            Show1deskLab(buffStNum/2);
                        else if (classRoom->GetPlan((buffStNum/2)%3+1,(buffStNum/6)+1) == 2)// Если за двухместной
                            Show2deskLab(buffStNum/2);
                    }
                }
            }
}

return false;
}

void MainWindow::LessonTime()
{
    stwtch->Start();
    if (stwtch->getMinutes() == 40)
    {
        ShowResultWin();
        BfrLsn();
    }
}

void MainWindow::ShowResultWin()
{
    int rezLearn = 0,rezDiscip = 0,rezIntrst = 0;
    int numberStudents = 0;
    QString str = "";
    QString str2;
    for (int k = 0; k<30; k++)
        {
            if (classRoom->students[k].getSex()!="")
            {
                str2 = (labLearn+k)->text();
                str2.resize(str2.size()-1);
                rezLearn+= str2.toInt();
                if (classRoom->students[k].getfDiscip()) rezDiscip++;
                if (classRoom->students[k].getfIntrst()) rezIntrst++;
                numberStudents++;
            }
        }
    rezLearn/=numberStudents;
    rezIntrst=(rezIntrst*100)/numberStudents;
    rezDiscip=(rezDiscip*100)/numberStudents;
    str+= "Усвоенный за урок материал в среднем: " + QString::number(rezLearn) + "%\n\nПроявивших интерес к уроку: "+ QString::number(rezIntrst) + "%\n\nИспытавших отрицательные эмоции: "+ QString::number(rezDiscip)+"%";
    QMessageBox msgBox;
    msgBox.setWindowTitle("  Результаты работы за урок");
    msgBox.setIcon(QMessageBox::NoIcon);
    msgBox.setText(str);
    msgBox.setWindowIcon(blank);
    timer->stop();     // Остановить секундомер
    timerLsn->stop();  // Остановить действия во время урока
    msgBox.exec();
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

// Показать символы-подсказки напротив каждого из учеников
void MainWindow::ShowHints()
{
    int wdth, hght;
    wdth = statNorm.width();hght = statNorm.height();
    for (int i = 0, j = 0, k = 0; k<30; i++, k+=2)
        {
            if (i == 3) {i = 0; j++;}
            if ((classRoom->GetPlan(i+1,j+1) == 1)||(classRoom->GetPlan(i+1,j+1) == 2))
            {
                (labSymbols+k)->setParent(this);
                (labLearn+k)->setParent(this);
                (labInterest+k)->setParent(this);
                (labDiscip+k)->setParent(this);
                // Смайлик в зависимости от склонности к нарушению дисциплины
                if (classRoom->students[k].getRuffian() >= 70)(labSymbols+k)->setPixmap(statEvil);
                else if (classRoom->students[k].getRuffian() < 30) (labSymbols+k)->setPixmap(statKind);
                else
                (labSymbols+k)->setPixmap(statNorm);
                (labLearn+k)->setText(QString::number(classRoom->students[k].getLearn()/100)+"%");
                (labInterest+k)->setText(QString::number(classRoom->students[k].getInterest())+"%");
                (labDiscip+k)->setText(QString::number(classRoom->students[k].getRuffian())+"%");
                (labSymbols+k)->setGeometry(142+i*160,315+j*100,wdth,hght);
                (labLearn+k)->setGeometry(162+i*160,315+j*100,60,9);
                (labInterest+k)->setGeometry(162+i*160,328+j*100,60,9);
                (labDiscip+k)->setGeometry(162+i*160,342+j*100,60,9);
                (labLearn+k)->setFont(QFont("Franklin Gothic Demi Cond", 9));
                (labInterest+k)->setFont(QFont("Franklin Gothic Demi Cond", 9));
                (labDiscip+k)->setFont(QFont("Franklin Gothic Demi Cond", 9));
                (labLearn+k)->setStyleSheet("QLabel {color: white;}");
                (labInterest+k)->setStyleSheet("QLabel {color: white;}");
                (labDiscip+k)->setStyleSheet("QLabel {color: white;}");
                (labSymbols+k)->show();
                (labLearn+k)->show();
                (labInterest+k)->show();
                (labDiscip+k)->show();
            }
            if (classRoom->GetPlan(i+1,j+1) == 2) // Если в плане двойная парта, то отобразить подсказку и для соседа
            {
                (labSymbols+k+1)->setParent(this);
                (labLearn+k+1)->setParent(this);
                (labInterest+k+1)->setParent(this);
                (labDiscip+k+1)->setParent(this);
                // Смайлик в зависимости от склонности к нарушению дисциплины
                if (classRoom->students[k+1].getRuffian() >= 70)(labSymbols+k+1)->setPixmap(statEvil);
                else if (classRoom->students[k+1].getRuffian() < 30) (labSymbols+k+1)->setPixmap(statKind);
                else
                (labSymbols+k+1)->setPixmap(statNorm);
                (labLearn+k+1)->setText(QString::number(classRoom->students[k+1].getLearn()/100)+"%");
                (labInterest+k+1)->setText(QString::number(classRoom->students[k+1].getInterest())+"%");
                (labDiscip+k+1)->setText(QString::number(classRoom->students[k+1].getRuffian())+"%");
                (labSymbols+k+1)->setGeometry(142+i*160+55,315+j*100,wdth,hght);
                (labLearn+k+1)->setGeometry(162+i*160+55,315+j*100,60,9);
                (labInterest+k+1)->setGeometry(162+i*160+55,328+j*100,60,9);
                (labDiscip+k+1)->setGeometry(162+i*160+55,342+j*100,60,9);
                (labLearn+k+1)->setFont(QFont("Franklin Gothic Demi Cond", 9));
                (labInterest+k+1)->setFont(QFont("Franklin Gothic Demi Cond", 9));
                (labDiscip+k+1)->setFont(QFont("Franklin Gothic Demi Cond", 9));
                (labLearn+k+1)->setStyleSheet("QLabel {color: white;}");
                (labInterest+k+1)->setStyleSheet("QLabel {color: white;}");
                (labDiscip+k+1)->setStyleSheet("QLabel {color: white;}");
                (labSymbols+k+1)->show();
                (labLearn+k+1)->show();
                (labInterest+k+1)->show();
                (labDiscip+k+1)->show();
            }
    }
}

void MainWindow::Show1deskLab(int deskNum)
{
    if (classRoom->students[deskNum*2].getSex() == "Девочка") (labels+deskNum)->setPixmap(deskG);      //Отобразить внешность ученика согласно его полу
    else if (classRoom->students[deskNum*2].getSex() == "Мальчик") (labels+deskNum)->setPixmap(deskB);
}

void MainWindow::Show2deskLab(int deskNum)
{
    if ((classRoom->students[deskNum*2].getSex() == "Девочка")&&((classRoom->students[deskNum*2+1].getSex() == "Девочка"))) (labels+deskNum)->setPixmap(deskGG);
    else if ((classRoom->students[deskNum*2].getSex() == "Девочка")&&((classRoom->students[deskNum*2+1].getSex() == "Мальчик"))) (labels+deskNum)->setPixmap(deskGB);
    else if ((classRoom->students[deskNum*2].getSex() == "Мальчик")&&((classRoom->students[deskNum*2+1].getSex() == "Девочка"))) (labels+deskNum)->setPixmap(deskBG);
    else if ((classRoom->students[deskNum*2].getSex() == "Мальчик")&&((classRoom->students[deskNum*2+1].getSex() == "Мальчик"))) (labels+deskNum)->setPixmap(deskBB);
}

// Вид экрана до начала урока
void MainWindow::BfrLsn()
{
    labMenu1->show();
    labMenu2->show();
    labDelete->show();
    labCounter->show();
    cmbbox->show();
    bCont->show();
    bDel->show();
    bExit->show();
    bFinLsn->hide();
    bPause->hide();
    bFinLsn->setEnabled(false); // До начала урока кнопки недоступны
    bPause->setEnabled(false);
    bPause->setText("Редактировать");
    labBoard->hide();
    labTab->hide();
    labMinutes->hide();
    labSeconds->hide();
    labStWtch->hide();
    labMinutes->setText("00");
    labSeconds->setText(":00");
    timer->stop();     // Остановить секундомер
    timerLsn->stop();  // Остановить действия во время урока
    // Картинки в меню
    labDelete->show();
    labMenu1->show();
    labMenu2->show();
    // Учитель
    labTcher->setPixmap(tcherMenu);
    labTcher->setPos(343,157);
    // Спрятать подсказки
    for (int i = 0, j = 0, k = 0; k<30; i++, k+=1)
        {
            if (i == 3) {i = 0; j++;}
            (labSymbols+k)->hide();
            (labLearn+k)->hide();
            (labInterest+k)->hide();
            (labDiscip+k)->hide();
        }
    // Парты
    for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if (classRoom->GetPlan(i+1,j+1) == 0)
                    (labels+k)->setPixmap(crossOff); // На пустые места - крестики
            }
}

void MainWindow::BeginLsn()
{  //Проверка: начать урок только если параметры указаны для всех учеников
    for(int j = 0, k = 0; j < 5; j++)
        for (int i = 0; i < 3; i++, k+=2)
            if (classRoom->GetPlan(i+1,j+1) != 0)
                if (classRoom->students[k].getSex() == "")
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(" ");
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setText("Параметры указаны не для всех учеников");
                    msgBox.setWindowIcon(blank);
                    msgBox.exec();
                    return;
                }
    // Если проверка пройдена, то начинается урок
    labMenu1->hide();
    labMenu2->hide();
    labDelete->hide();
    labCounter->hide();
    cmbbox->hide();
    bCont->hide();
    bDel->hide();
    bExit->hide();
    bFinLsn->show();
    bPause->show();
    labTab->show();
    classRoom->subject->setSubj(cmbbox->currentText());
    classRoom->subject->showBlackboard(labBoard);
    classRoom->clearStFlags();
    for (int i = 0, j = 0, k = 0; k < 15; i++, k++)
            {
                if (i == 3) {i = 0; j++;}
                if (classRoom->GetPlan(i+1,j+1) == 0)
                    (labels+k)->clear(); // Убрать крестики, оставить только парты
                else
                {// Вычислить начальные значения показателей усвоения урока, интереса, дисциплины
                    classRoom->StInitHints(k*2);
                    if (classRoom->GetPlan(i+1,j+1) == 2)
                        classRoom->StInitHints(k*2+1);
                }
            }
    m_player->play();
    labTcher->hide();
    time->restart();          // Начать отсчет времени
    timer2->start(100);       // Запустить анимацию захода учителя в класс
    labMinutes->show();labSeconds->show();labStWtch->show(); // Секундомер
}

// Происходящее во время урока
void MainWindow::DuringLsn()
{
    for (int i = 0, j = 0, k = 0; k < 30; i++, k+=2)
    {
        if (i == 3) {i = 0; j++;}
        if ((classRoom->GetPlan(i+1,j+1) == 1)||(classRoom->GetPlan(i+1,j+1) == 2))
            classRoom->StLearning(k);
        if (classRoom->GetPlan(i+1,j+1) == 2)
            classRoom->StLearning(k+1);
    }
    ChangeHints();
}

// Изменение значения показателей деят-ности ученика в подсказках
void MainWindow::ChangeHints()
{
    int min = 0, sec = 0;
    int dis;
    double xa,ya,l;
    double lrnng;
    for (int i = 0, j = 0, k = 0; k < 30; i++, k+=2)
    {
                if (i == 3) {i = 0; j++;}
                if ((classRoom->GetPlan(i+1,j+1) == 1)||(classRoom->GetPlan(i+1,j+1) == 2))
                {
                    dis = classRoom->students[k].getDiscip();
                    lrnng = classRoom->students[k].getLearn()/100;

                    min = labMinutes->text().toInt();
                    sec = (labSeconds->text()).remove(0,1).toInt();

                    l = classRoom->students[k].getLearn();
                    xa = (min*60+sec)/24+1; // Время
                    ya = l/100.0;
                    lrnng=100.0*(ya/xa);
                    if (lrnng>100) lrnng = 100;
                    int ll = lrnng;
                    (labLearn+k)->setText(QString::number(ll) + "%");
                    (labInterest+k)->setText(QString::number(classRoom->students[k].getInterest()) + "%");
                    (labDiscip+k)->setText(QString::number(dis) + "%");
                    if (dis < 30) (labSymbols+k)->setPixmap(statKind);
                    else if (dis >= 70) (labSymbols+k)->setPixmap(statEvil);
                    else (labSymbols+k)->setPixmap(statNorm);
                }
                if (classRoom->GetPlan(i+1,j+1) == 2)
                {
                    dis = classRoom->students[k+1].getDiscip();
                    lrnng = classRoom->students[k+1].getLearn()/100;
                    min = labMinutes->text().toInt();
                    sec = (labSeconds->text()).remove(0,1).toInt();
                    l = classRoom->students[k+1].getLearn();
                    xa = (min*60+sec)/24+1; // Время
                    ya = l/100.0;
                    lrnng=100.0*(ya/xa);
                    if (lrnng>100) lrnng = 100;
                    int ll = lrnng;
                    (labLearn+k+1)->setText(QString::number(ll) + "%");
                    (labInterest+k+1)->setText(QString::number(classRoom->students[k+1].getInterest()) + "%");
                    (labDiscip+k+1)->setText(QString::number(dis) + "%");
                    if (dis < 30) (labSymbols+k+1)->setPixmap(statKind);
                    else if (dis >= 70) (labSymbols+k+1)->setPixmap(statEvil);
                    else (labSymbols+k+1)->setPixmap(statNorm);

                    /*dis = classRoom->getStDiscip(k+1);
                    (labLearn+k+1)->setText(QString::number(classRoom->getStLearn(k+1)/100) + "%");
                    (labInterest+k+1)->setText(QString::number(classRoom->getStInterest(k+1)) + "%");
                    (labDiscip+k+1)->setText(QString::number(dis) + "%");
                    if (dis < 30) (labSymbols+k+1)->setPixmap(statKind);
                    else if (dis >= 70) (labSymbols+k+1)->setPixmap(statEvil);
                    else (labSymbols+k+1)->setPixmap(statNorm);*/
                }
    }
}

void MainWindow::Pause()
{
    if (timer->isActive()) // Если пауза не стоит, поставить на паузу
    {
        bPause->setText("Продолжить");
        timer->stop();      // Остановить секундомер
        timerLsn->stop();   // Остановить действия во время урока
    }
    else // Если урок уже на паузе, то продолжить
    {
        bPause->setText("Редактировать");
        timer->start();     // Секундомер продолжает отсчет
        timerLsn->start(); // Продолжить действия во время урока
    }
}

// Учитель заходит в класс
void MainWindow::tcherGoes()
{
    static int frame = 1, x = 590, f = 0;
    if ((time->elapsed() >= 1000)&&(time->elapsed() <= 2000))
    {
        labTcher->show();
        palette.setBrush(QPalette::Background, bkgndOp);
        this->setPalette(palette);
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
    labTcher->setPos(x,150);
    x-=5;
    if (x == 350) // Дошла до стула
    {
        labTcher->setPixmap(tcherSits);
        labTcher->setPos(343,157);
        bFinLsn->setEnabled(true);
        bPause->setEnabled(true);
        timer2->stop();   // Отключение таймера по достижении объектом нужной точки на экране
        timer->start(125);// Запустить секундомер
        ShowHints();
        timerLsn->start(1250);
        x = 590;
        f = 0;
    }
}
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
     if(msgBox.clickedButton() == yes)
     {
         DeleteAllDesks();
         classRoom->teacher->SetTeacher("Учитель",100,50,50,50);
         for (int i = 0, j = 0, k = 0; k < 30; i++, k++)
                 { // Удалить данные всех учеников
                     if (i == 3) {i = 0; j++;}
                     classRoom->students[k].setStudent("Ученик","",100,50,50,50,50);
                 }
     }
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

void MainWindow::on_bFinLsn_clicked()
{
    ShowResultWin();
    BfrLsn();
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



/*void MainWindow::Stopwatch()
{
    static int min = 0,sec = 0;
    sec = ((labSeconds->text()).remove(0,1)).toInt();
    min = (labMinutes->text()).toInt();
    sec++;
    if (sec == 60)
    {
        min++;
        sec = 0;
    }
    if (min < 10) labMinutes->setText("0" + QString::number(min));
    else labMinutes->setText(QString::number(min));
    if (sec < 10) labSeconds->setText(":0"+QString::number(sec));
    else labSeconds->setText(":"+QString::number(sec));
    if (min == 40) timer->stop();
}*/
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
