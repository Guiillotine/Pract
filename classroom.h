#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "human.h"

class ClassRoom
{
public:
    ClassRoom();
    void EditPlan(int row, int number, int value);// Редактирование плана расположения парт
    int GetPlan(int row, int number);// Узнать, какая парта находится в звдвнном ряду на заданном месте
    void setStudent(int numberSt, QString fio,QString sex,int health,int concentr,int humanit,int technical,int badGuy);
    QString getFio(int numberSt);
    QString getSex(int numberSt);
    int getStConcentr(int numberSt);
    int getStHumanit(int numberSt);
    int getStTechnical(int numberSt);
    int getStRuffian(int numberSt);
    int getStHealth(int numberSt);
private:                                   // (ряд, номер парты в нём, вид парты 0-нет,1-одномест.,2-двухмест.)
    int plan[5][3] = {0};                  // План расположения парт в классе
    class Student : public Human           // Внутренний класс - ученик
    {
    public:
        Student();
        //Student(QString fio,int health,int concentr,int humanit,int technical,int badGuy);
        QString sex;  // Пол ученика
        int concentr; // Способность к концентрации
        int humanit;  // Склонность к гуманитарным наукам
        int technical;// Склонность к техническим наукам
        int ruffian;  // Нарушение дисциплины
    };
    Student *students;  // Ученики в классе
};

#endif // CLASSROOM_H

