#include "classroom.h"

ClassRoom::ClassRoom()
{
    students = new Student[30]; // Максимально возможное количество учеников - 30
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
    fio = "УЧЕНЫЦА";
    health = 100;
    concentr = 50;
    humanit = 50;
    technical = 50;
    ruffian = 0;
}

ClassRoom::Student::Student(QString fio, int health, int concentr, int humanit, int technical, int ruffian)
{
    if (health < 0) health = 0; if (health > 99) health = 99;
    if (concentr < 0) concentr = 0; if (concentr > 99) concentr = 99;
    if (humanit < 0) humanit = 0; if (humanit > 99) humanit = 99;
    if (technical < 0) technical = 0; if (technical > 99) technical = 99;
    if (ruffian < 0) ruffian = 0; if (ruffian > 99) ruffian = 99;
    this->fio = fio;
    this->health = health;
    this->concentr = concentr;
    this->humanit = humanit;
    this->technical = technical;
    this-> ruffian = ruffian;
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

QString ClassRoom::getFio(int numberSt)
{
    return (students+numberSt)->fio;
}

QString ClassRoom::getSex(int numberSt)
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
