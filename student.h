#ifndef STUDENT_H
#define STUDENT_H
#include "human.h"              // Класс "Человек"

class Student : public Human           // Класс ученик
{
public:
    Student();
    Student(QString fio,int health,int concentr,int humanit,int technical,int badGuy);
    int concentr; // Способность к концентрации
    int humanit;  // Склонность к гуманитарным наукам
    int technical;// Склонность к техническим наукам
    int ruffian;  // Нарушение дисциплины
};

#endif // STUDENT_H
