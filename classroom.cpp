#include "classroom.h"
#include <QMessageBox>
ClassRoom::ClassRoom()
{
    students = new Student[31]; // Максимально возможное количество учеников - 30, +1 - буфер для пересадки
    teacher = new Teacher();
    subject = new Subject();
    BuffStNum = -1; // Номер ученика при пересадке
}

ClassRoom::~ClassRoom()
{
    delete subject;
    delete teacher;
    delete[] students;
}

void ClassRoom::EditPlan(int row, int number, int value)
{
    if ((row < 1)||(row > 3)||(number < 1)||(number > 5)) // Существуют ли указанный ряд и номер парты в плане
        return;
    if ((value<0)||(value>2)) // Корректно ли указан вид парты
        return;
    plan[number-1][row-1]=value;
}

int ClassRoom::GetPlan(int row, int number)
{
    if ((row < 1)||(row > 3)||(number < 1)||(number > 5)) // Существуют ли указанный ряд и номер парты в плане
        return 0;
    return plan[number-1][row-1];
}

ClassRoom::Student::Student()
{
    fio = "Ученик";
    sex = "";
    health = 100;
    concentr = 50;
    humanit = 50;
    technical = 50;
    ruffian = 50;
    learn = 0;     // Усвоение материала
    interest = 50; // Интерес
    discip = 50;   // Дисциплина
    fDiscip = 0;   // Злился ли ученик
    fIntrst = 0;   // Был ли ученик заинтересован
}

void ClassRoom::Student::initHints()
{
    if (interest > 100) interest = 100;
    learn = 0;
    discip = ruffian;
}

void ClassRoom::Student::addNegative(int disc)
{
    float ruf = ruffian;
    if ((disc > discip)&&(discip < 100))
    {
        discip = discip + ((disc - discip)/5)*(ruf/50);
    }
    if (discip > 100) discip = 100;
}

void ClassRoom::Student::subNegative(int deskNum)
{
    int place = deskNum/3; // Номер места в ряду
    discip = discip - (25 - place*5); // Чем дальше от учителя, тем меньше его влияние
    if (discip < 40) discip = 40;
}

void ClassRoom::Student::addLearn(int deskNum,int comm)
{
    int place = deskNum/3; // Номер места в ряду
    double maxLearn = 41.666666667;
    maxLearn = maxLearn - (99-health)/5;

    int tmp = discip/70;
    maxLearn = maxLearn - tmp*10;   // Начиная с 70 негатив начинает влиять на успеваемость
    if (discip>=80) maxLearn-=10;   // Дополнительно отнять 10, если негатив превышает 80
    if (discip>=90) maxLearn-=10;   // Дополнительно отнять 10, если негатив превышает 90

    if (concentr>55) maxLearn = maxLearn + (concentr-55)/2;  // Способность к концентрации > среднего - положительное влияние на успеваемость
    if (interest>55) maxLearn+= (interest-55)/2;             // Если ученик заинтересован уроком, это положительно влияет на успеваемость
    if (comm>55) maxLearn+= ((comm-55)/2);                   // Если учитель обладает хорошими коммуникативными способностями - полож. влияние на успеваемость (+ завис.от места)
    if (maxLearn > 41.666666667) maxLearn = 41.666666667;
    if (concentr<45) maxLearn = maxLearn - (45 - concentr)/2;// Если сп. к конц. < среднего - отрицательное влияние
    if (interest<45) maxLearn-= (45 - interest)/2;           // Если ученик не заинтересован уроком - отрицательное влияние
    if (comm<45) maxLearn = maxLearn - (45 - comm)/2;        // Если учитель не обладает коммуникативными способностями - отр. влияние

    maxLearn = maxLearn - place*2; // Чем дальше от учителя, тем хуже усваиваются знания

    if (maxLearn<0) maxLearn=0;
    learn+=maxLearn;
    if (learn > 10000) learn = 10000;
}

void ClassRoom::Student::changeIntrst(int creat, int hum,int tech)
{
    if ((hum==0)&&(tech==100))// Математика
    {
        interest = technical;
    }
    if ((hum==100)&&(tech==0))// Русский язык
    {
        interest = humanit;
    }
    if ((hum==70)&&(tech==30))// История
    {
        interest = (humanit*70 + technical*30)/100;
    }
    if ((hum==50)&&(tech==50))// География
    {
        interest = (humanit*50 + technical*50)/100;
    }
    interest = interest + creat/4; // Креативность учителя положительно влияет на интерес ученика
    interest = interest - (99-health)/3;  // Если ученик плохо себя чувствует, интерес снизится
    if (ruffian >= 50) interest-=20; // Склонным к нарушению дисциплины сложнее проявлять интерес
    if (discip>=70) interest -= discip-50;// Если ученик ощущает негатив, интерес снизится
    if (interest > 100) interest = 100;
    if (interest < 0) interest = 0;
}

void ClassRoom::Student::setStudent(QString fio,QString sex, int health, int concentr, int humanit, int technical, int ruffian)
{
    if (health < 0) health = 0; if (health > 99) health = 99;
    if (concentr < 0) concentr = 0; if (concentr > 99) concentr = 99;
    if (humanit < 0) humanit = 0; if (humanit > 99) humanit = 99;
    if (technical < 0) technical = 0; if (technical > 99) technical = 99;
    if (ruffian < 0) ruffian = 0; if (ruffian > 99) ruffian = 99;
    this->fio = fio;
    this->sex = sex;
    this->health = health;
    this->concentr = concentr;
    this->humanit = humanit;
    this->technical = technical;
    this-> ruffian = ruffian;
}

void ClassRoom::Student::setHints(int learn, int interest, int discip)
{
    this->learn = learn;
    this->interest = interest;
    this->discip = discip;
}

void ClassRoom::CopySt(int numberSt) // Скопировать данные указанного ученика в конец массива учеников (буфер)
{
    (students+30)->setStudent((students+numberSt)->getFio(), (students+numberSt)->getSex(), (students+numberSt)->getHealth(), (students+numberSt)->getConcentr(), (students+numberSt)->getHumanit(), (students+numberSt)->getTechnical(), (students+numberSt)->getRuffian());
    BuffStNum = numberSt;
}

void ClassRoom::PasteSt(int numberSt) // Скопировать данные из конца массива учеников (буфера) в указанного ученика
{
    if ((students+numberSt)->getSex()!="")
    {
        ClassRoom tmp;
        // Копировать данные ученика, на место которого совершена вставка из буфера
        tmp.students[0].setStudent(students[numberSt].getFio(), students[numberSt].getSex(), students[numberSt].getHealth(), students[numberSt].getConcentr(), students[numberSt].getHumanit(), students[numberSt].getTechnical(), students[numberSt].getRuffian());
        tmp.students[0].setHints(students[numberSt].getLearn(), students[numberSt].getInterest(), students[numberSt].getDiscip());
        // Вставка из буффера
        students[numberSt].setStudent(students[BuffStNum].getFio(), students[BuffStNum].getSex(), students[BuffStNum].getHealth(), students[BuffStNum].getConcentr(), students[BuffStNum].getHumanit(), students[BuffStNum].getTechnical(), students[BuffStNum].getRuffian());
        students[numberSt].setHints(students[BuffStNum].getLearn(), students[BuffStNum].getInterest(), students[BuffStNum].getDiscip());
        // Вставка из временного объекта на место, с которого было совершено копирование
        students[BuffStNum].setStudent(tmp.students[0].getFio(), tmp.students[0].getSex(), tmp.students[0].getHealth(), tmp.students[0].getConcentr(), tmp.students[0].getHumanit(), tmp.students[0].getTechnical(), tmp.students[0].getRuffian());
        students[BuffStNum].setHints(tmp.students[0].getLearn(), tmp.students[0].getInterest(), tmp.students[0].getDiscip());
        students[30].setStudent(students[30].getFio(),"",0,0,0,0,0); // Очистить буфер
    }
}

void ClassRoom::Student::DelSt()
{
    setStudent("Ученик","",100,50,50,50,50);
}

void ClassRoom::StLearning(int numberSt)
{
    int numberDsk = numberSt/2;
    int x = numberDsk/3; int y = numberDsk%3;
    int fEvil = 0;
    int maxNegNum = -1;
    int st = teacher->getStrict();
    int cr = teacher->getCreat();
    int com = teacher->getComm();
    int tHlth = teacher->health;
    // Все способности учителя зависят от его здоровья
    st = st - (99-tHlth)/3;
    cr = cr - (99-tHlth)/3;
    com = com - (99-tHlth)/3;

    // Чем больше склонность к нарушению дисциплины, тем больше вероятность совершения проступка
    if ((rand() % 20 == 12)&&(((students+numberSt)->getRuffian() > 50))||((students+numberSt)->getDiscip() >= 90))  fEvil = 1;
    if ((rand() % 20 == 12)&&((students+numberSt)->getRuffian() >= 80)) fEvil = 1; // Увеличить вероятность в 2 раза

    // Чем больше строгость учителя, тем больше случаев снижения негатива у учеников
    if ((st >= 90)&&(rand() % 2))
    {
        maxNegNum = MaxNegSearch();
        if (maxNegNum!=-1) (students+maxNegNum)->subNegative(maxNegNum/2);
    }
    else if (rand() % (1000/(st+1)) == 3)
    {
        maxNegNum = MaxNegSearch();
        if (maxNegNum!=-1) (students+maxNegNum)->subNegative(maxNegNum/2);
    }

    if (fEvil) (students+numberSt)->addNegative((students+numberSt)->getDiscip()+50);
    if ((students+numberSt)->getDiscip() >= 70) (students+numberSt)->setfDiscip(); // Злился ли ученик

    if (((students+numberSt+1)->getSex()!="")&&(numberSt%2 == 0)) // Если есть сосед по парте справа
        if (fEvil) (students+(numberSt+1))->addNegative((students+numberSt)->getDiscip()+10);
    if (numberSt%2) // Если есть сосед по парте слева
        if (fEvil) (students+(numberSt-1))->addNegative((students+numberSt)->getDiscip()+10);

    if ((x - 1 >= 0)&&((students+(((x-1)*3+y)*2))->getSex()!=""))
        if (fEvil)
        {
            int n = ((x-1)*3+y)*2;
            (students+n)->addNegative((students+numberSt)->getDiscip());
            if ((students+n+1)->getSex()!="")
                (students+n+1)->addNegative((students+numberSt)->getDiscip());
        }
    if ((x + 1 <= 4)&&((students+((x+1)*3+y)*2))->getSex()!="")
        if (fEvil)
        {
            int n = ((x+1)*3+y)*2;
            (students + n)->addNegative((students+numberSt)->getDiscip());
            if ((students+n+1)->getSex()!="")
                (students+n+1)->addNegative((students+numberSt)->getDiscip());
        }
    if ((y + 1 <= 2)&&((students+(x*3+(y+1))*2)->getSex()!=""))
        if (fEvil)
        {
            int n = (x*3+(y+1))*2;
            (students+n)->addNegative((students+numberSt)->getDiscip());
            if ((students+n+1)->getSex()!="")
            {
                (students+n+1)->addNegative((students+numberSt)->getDiscip());
            }
        }
    if ((y - 1 >= 0)&&((students+(x*3+(y-1))*2)->getSex()!=""))
        if (fEvil)
        {
            int n = (x*3+(y-1))*2;
            (students+n)->addNegative((students+numberSt)->getDiscip());
            if ((students+n+1)->getSex()!="")
            {
                (students+n+1)->addNegative((students+numberSt)->getDiscip());
            }
        }
    (students+numberSt)->changeIntrst(cr,subject->getHumanit(),subject->getTechnical());
    if ((students+numberSt)->getInterest() >= 50) (students+numberSt)->setfIntrst(); // Был ли ученик заинтересован уроком
    (students+numberSt)->addLearn(numberDsk,com); // Усвоение урока

    /*QString str = QString::number(numberDsk) + " ";
    for(int i = 0; i < 8; i++)
    {
        str=str+QString::number(discArr[i])+ " ";
    }
    QMessageBox msgBox;
    msgBox.setWindowTitle(str);
    msgBox.setText(str);
    msgBox.exec();*/

    fEvil = 0;
}

void ClassRoom::StInitHints(int numberSt)
{
    (students+numberSt)->changeIntrst(teacher->getCreat(),subject->getHumanit(),subject->getTechnical());
    (students+numberSt)->initHints();
}

void ClassRoom::clearStFlags()
{
    for (int i = 0; i < 30; i++)
    {
        (students+i)->clearFlags();
    }
}

QString ClassRoom::Student::getSex()
{
    return sex;
}

int ClassRoom::Student::getConcentr()
{
    return concentr;
}

int ClassRoom::Student::getHumanit()
{
    return humanit;
}

int ClassRoom::Student::getTechnical()
{
    return technical;
}

int ClassRoom::Student::getRuffian()
{
    return ruffian;
}

int ClassRoom::Student::getLearn()
{
    return learn;
}

int ClassRoom::Student::getInterest()
{
    return interest;
}

int ClassRoom::Student::getDiscip()
{
    return discip;
}

int ClassRoom::Student::getfDiscip()
{
    return fDiscip;
}

void ClassRoom::Student::setfDiscip()
{
    fDiscip = 1;
}

int ClassRoom::Student::getfIntrst()
{
    return fIntrst;
}

void ClassRoom::Student::setfIntrst()
{
    fIntrst = 1;
}

void ClassRoom::Student::clearFlags()
{
    fDiscip = 0;
    fIntrst = 0;
}

int ClassRoom::getBuffStNum()
{
    return BuffStNum;
}

int ClassRoom::MaxNegSearch()
{
    int numb = -1;
    int max = -1;
    for (int i = 0; i < 30; i++)
        if (((students + i)->getSex() != "")&&(max < (students + i)->getDiscip())&&((students + i)->getDiscip() > 50))
        {
            max = (students + i)->getDiscip();
            numb = i;
        }
    return numb;
}

void ClassRoom::Teacher::SetTeacher(QString fio, int health, int communication, int creativity, int strictness)
{
    this->fio = fio;
    this->health = health;
    this->communication = communication;
    this->creativity = creativity;
    this->strictness = strictness;
}

int ClassRoom::Teacher::getComm()
{
    return communication;
}

int ClassRoom::Teacher::getCreat()
{
    return creativity;
}

int ClassRoom::Teacher::getStrict()
{
    return strictness;
}

ClassRoom::Teacher::Teacher()
{
    fio = "Учитель";
    communication = 50;// Коммунитативные способности
    creativity = 50;   // Креативность
    strictness = 50;   // Строгость
}
