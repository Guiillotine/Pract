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
    void CopySt(int numberSt); // Скопировать данные указанного ученика в конец массива учеников (буфер)
    void PasteSt(int numberSt);// Скопировать данные из конца массива учеников (буфера) в указанного ученика
    QString getStFio(int numberSt);
    QString getStSex(int numberSt);
    int getStConcentr(int numberSt);
    int getStHumanit(int numberSt);
    int getStTechnical(int numberSt);
    int getStRuffian(int numberSt);
    int getStHealth(int numberSt);
    int getBuffStNum();
    void SetTeatcher(QString fio,int health,int communication, int creativity, int strictness);
    QString getTchrFio();
    int getTchrHealth();
    int getTchrComm();
    int getTchrCreat();
    int getTchrStrict();
private:                                   // (ряд, номер парты в нём, вид парты 0-нет,1-одномест.,2-двухмест.)
    int plan[5][3] = {0};                  // План расположения парт в классе
    int BuffStNum;                         // Буфер для номера ученика при пересадке

    class Teacher : public Human           // Внутренний класс - учитель
    {
    public:
        Teacher();
        int communication;// Коммунитативные способности
        int creativity;   // Креативность
        int strictness;   // Строгость
    };
    Teacher *teatcher;     // Учитель
    class Student : public Human           // Внутренний класс - ученик
    {
    public:
        Student();
        QString sex;  // Пол ученика
        int concentr; // Способность к концентрации
        int humanit;  // Склонность к гуманитарным наукам
        int technical;// Склонность к техническим наукам
        int ruffian;  // Нарушение дисциплины
    };
    Student *students;  // Ученики в классе
};

#endif // CLASSROOM_H

