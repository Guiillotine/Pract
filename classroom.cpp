#include "classroom.h"
#include <QMessageBox>
ClassRoom::ClassRoom()
{
    students = new Student[31]; // Максимально возможное количество учеников - 30, +1 - буфер для пересадки
    teatcher = new Teacher();
    subject = new Subject();
    BuffStNum = -1; // Номер ученика при пересадке
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
    if (discip>=70) interest -= discip-50;// Если ученик ощущает негатив, интерес снизится
    if (interest > 100) interest = 100;
    if (interest < 0) interest = 0;
}

void ClassRoom::setStudent(int numberSt, QString fio,QString sex, int health, int concentr, int humanit, int technical, int ruffian)
{
    if (health < 0) health = 0; if (health > 99) health = 99;
    if (concentr < 0) concentr = 0; if (concentr > 99) concentr = 99;
    if (humanit < 0) humanit = 0; if (humanit > 99) humanit = 99;
    if (technical < 0) technical = 0; if (technical > 99) technical = 99;
    if (ruffian < 0) ruffian = 0; if (ruffian > 99) ruffian = 99;
    (students+numberSt)->fio = fio;
    (students+numberSt)->sex = sex;
    (students+numberSt)->health = health;
    (students+numberSt)->concentr = concentr;
    (students+numberSt)->humanit = humanit;
    (students+numberSt)->technical = technical;
    (students+numberSt)-> ruffian = ruffian;
}

void ClassRoom::setHints(int numberSt, int learn, int interest, int discip)
{
    (students+numberSt)->learn = learn;
    (students+numberSt)->interest = interest;
    (students+numberSt)->discip = discip;
}

void ClassRoom::CopySt(int numberSt) // Скопировать данные указанного ученика в конец массива учеников (буфер)
{
    setStudent(30, getStFio(numberSt), getStSex(numberSt), getStHealth(numberSt), getStConcentr(numberSt), getStHumanit(numberSt), getStTechnical(numberSt), getStRuffian(numberSt));
    BuffStNum = numberSt;
}

void ClassRoom::PasteSt(int numberSt) // Скопировать данные из конца массива учеников (буфера) в указанного ученика
{
    if (getStSex(numberSt)!="")
    {
        ClassRoom tmp;
        // Копировать данные ученика, на место которого совершена вставка из буфера
        tmp.setStudent(0, getStFio(numberSt), getStSex(numberSt), getStHealth(numberSt), getStConcentr(numberSt), getStHumanit(numberSt), getStTechnical(numberSt), getStRuffian(numberSt));
        tmp.setHints(0, getStLearn(numberSt), getStInterest(numberSt), getStDiscip(numberSt));
        // Вставка из буффера
        setStudent(numberSt, getStFio(BuffStNum), getStSex(BuffStNum), getStHealth(BuffStNum), getStConcentr(BuffStNum), getStHumanit(BuffStNum), getStTechnical(BuffStNum), getStRuffian(BuffStNum));
        setHints(numberSt, getStLearn(BuffStNum), getStInterest(BuffStNum), getStDiscip(BuffStNum));
        // Вставка из временного объекта на место, с которого было совершено копирование
        setStudent(BuffStNum, tmp.getStFio(0), tmp.getStSex(0), tmp.getStHealth(0), tmp.getStConcentr(0), tmp.getStHumanit(0), tmp.getStTechnical(0), tmp.getStRuffian(0));
        setHints(BuffStNum, tmp.getStLearn(0), tmp.getStInterest(0), tmp.getStDiscip(0));
        setStudent(30,getStFio(30),"",0,0,0,0,0); // Очистить буфер
    }
}

void ClassRoom::DelSt(int numberSt)
{
    setStudent(numberSt,"Ученик","",100,50,50,50,0);
}

void ClassRoom::StLearning(int numberSt)
{
    int numberDsk = numberSt/2;
    int x = numberDsk/3; int y = numberDsk%3;
    int fEvil = 0;
    int maxNegNum = -1;
    int st = teatcher->strictness;
    int cr = teatcher->creativity;
    int com = teatcher->communication;
    int tHlth = teatcher->health;
    // Все способности учителя зависят от его здоровья
    st= st - (99-tHlth)/3;
    cr= cr - (99-tHlth)/3;
    com = com - (99-tHlth)/3;

    // Чем больше склонность к нарушению дисциплины, тем больше вероятность совершения проступка
    if ((rand() % 20 == 12)&&(((students+numberSt)->ruffian > 50))||((students+numberSt)->discip >= 90))  fEvil = 1;
    if ((rand() % 20 == 12)&&((students+numberSt)->ruffian >= 80)) fEvil = 1; // Увеличить вероятность в 2 раза

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

    if (fEvil) (students+numberSt)->addNegative((students+numberSt)->discip+50);
    if ((students+numberSt)->discip >= 70) setStfDiscip(numberSt); // Злился ли ученик

    if ((x - 1 >= 0)&&(getStSex(((x-1)*3+y)*2))!="")
    {
        if (fEvil) (students+((x-1)*3+y)*2)->addNegative((students+numberSt)->discip);
    }
    if ((x + 1 <= 4)&&(getStSex(((x+1)*3+y)*2))!="")
    {
        if (fEvil) (students+((x+1)*3+y)*2)->addNegative((students+numberSt)->discip);
    }
    if ((y + 1 <= 2)&&(getStSex((x*3+(y+1))*2)!=""))
    {
        if (fEvil) (students+(x*3+(y+1))*2)->addNegative((students+numberSt)->discip);
    }
    if ((y - 1 >= 0)&&(getStSex((x*3+(y-1))*2)!=""))
    {
        if (fEvil) (students+(x*3+(y-1))*2)->addNegative((students+numberSt)->discip);
    }
    (students+numberSt)->changeIntrst(cr,subject->getHumanit(),subject->getTechnical());
    if ((students+numberSt)->interest >= 50) setStfIntrst(numberSt); // Был ли ученик заинтересован уроком
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
    (students+numberSt)->changeIntrst(teatcher->creativity,subject->getHumanit(),subject->getTechnical());
    (students+numberSt)->initHints();
}

QString ClassRoom::getStFio(int numberSt)
{
    return (students+numberSt)->fio;
}

QString ClassRoom::getStSex(int numberSt)
{
    return (students+numberSt)->sex;
}

int ClassRoom::getStConcentr(int numberSt)
{
    return (students+numberSt)->concentr;
}

int ClassRoom::getStHumanit(int numberSt)
{
    return (students+numberSt)->humanit;
}

int ClassRoom::getStTechnical(int numberSt)
{
    return (students+numberSt)->technical;
}

int ClassRoom::getStRuffian(int numberSt)
{
    return (students+numberSt)->ruffian;
}

int ClassRoom::getStHealth(int numberSt)
{
    return (students+numberSt)->health;
}

int ClassRoom::getStLearn(int numberSt)
{
    return (students+numberSt)->learn;
}

int ClassRoom::getStInterest(int numberSt)
{
    return (students+numberSt)->interest;
}

int ClassRoom::getStDiscip(int numberSt)
{
    return (students+numberSt)->discip;
}

int ClassRoom::getStfDiscip(int numberSt)
{
    return (students+numberSt)->fDiscip;
}

void ClassRoom::setStfDiscip(int numberSt)
{
    (students+numberSt)->fDiscip = 1;
}

int ClassRoom::getStfIntrst(int numberSt)
{
    return (students+numberSt)->fIntrst;
}

void ClassRoom::setStfIntrst(int numberSt)
{
    (students+numberSt)->fIntrst = 1;
}

void ClassRoom::clearStFlags()
{
    for (int i = 0; i < 30; i++)
    {
        (students+i)->fDiscip = 0;
        (students+i)->fIntrst = 0;
    }
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
        if ((getStSex(i) != "")&&(max < getStDiscip(i))&&(getStDiscip(i) > 50))
        {
            max = getStDiscip(i);
            numb = i;
        }
    return numb;
}

void ClassRoom::SetTeatcher(QString fio, int health, int communication, int creativity, int strictness)
{
    teatcher->fio = fio;
    teatcher->health = health;
    teatcher->communication = communication;
    teatcher->creativity = creativity;
    teatcher->strictness = strictness;
}

QString ClassRoom::getTchrFio()
{
    return teatcher->fio;
}

int ClassRoom::getTchrHealth()
{
    return teatcher->health;
}

int ClassRoom::getTchrComm()
{
    return teatcher->communication;
}

int ClassRoom::getTchrCreat()
{
    return teatcher->creativity;
}

int ClassRoom::getTchrStrict()
{
    return teatcher->strictness;
}

ClassRoom::Teacher::Teacher()
{
    fio = "Учитель";
    communication = 50;// Коммунитативные способности
    creativity = 50;   // Креативность
    strictness = 50;   // Строгость
}
