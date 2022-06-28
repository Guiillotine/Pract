#include "classroom.h"

ClassRoom::ClassRoom()
{
    students = new Student[31]; // Максимально возможное количество учеников - 30, +1 - буфер для пересадки
    teatcher = new Teacher();
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
    ruffian = 0;
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
        // Вставка из буффера
        setStudent(numberSt, getStFio(30), getStSex(30), getStHealth(30), getStConcentr(30), getStHumanit(30), getStTechnical(30), getStRuffian(30));
        // Вставка из временного объекта на место, с которого было совершено копирование
        setStudent(getBuffStNum(), tmp.getStFio(0), tmp.getStSex(0), tmp.getStHealth(0), tmp.getStConcentr(0), tmp.getStHumanit(0), tmp.getStTechnical(0), tmp.getStRuffian(0));
        setStudent(30,getStFio(30),"",0,0,0,0,0); // Очистить буфер
    }
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

int ClassRoom::getBuffStNum()
{
    return BuffStNum;
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
