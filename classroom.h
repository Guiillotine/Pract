#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "human.h"
#include "subject.h"

class ClassRoom
{
public:
    ClassRoom();
    void EditPlan(int row, int number, int value);// Редактирование плана расположения парт
    int GetPlan(int row, int number);// Узнать, какая парта находится в звдвнном ряду на заданном месте
    void setStudent(int numberSt, QString fio,QString sex,int health,int concentr,int humanit,int technical,int ruffian);
    void CopySt(int numberSt); // Скопировать данные указанного ученика в конец массива учеников (буфер)
    void PasteSt(int numberSt);// Скопировать данные из конца массива учеников (буфера) в указанного ученика
    void DelSt(int numberSt);  // Удалить из списка данные студента с заданным номером
    void StLearning(int numberSt);// Происходящее в процессе обучения с учеником
    void StInitHints(int numberSt);
    QString getStFio(int numberSt);
    QString getStSex(int numberSt);
    int getStConcentr(int numberSt);
    int getStHumanit(int numberSt);
    int getStTechnical(int numberSt);
    int getStRuffian(int numberSt);
    int getStHealth(int numberSt);    
    int getStLearn(int numberSt);
    int getStInterest(int numberSt);
    int getStDiscip(int numberSt);
    int getStfDiscip(int numberSt);
    void setStfDiscip(int numberSt);
    int getStfIntrst(int numberSt);
    void setStfIntrst(int numberSt);
    void clearStFlags();
    int getBuffStNum();
    int MaxNegSearch(); // Поиск ученика с максимальным уровнем негатива
    void SetTeatcher(QString fio,int health,int communication, int creativity, int strictness);
    QString getTchrFio();
    int getTchrHealth();
    int getTchrComm();
    int getTchrCreat();
    int getTchrStrict();
    Subject *subject;                      // Школьный предмет
private:                                   // (ряд, номер парты в нём, вид парты 0-нет,1-одномест.,2-двухмест.)
    void setHints(int numberSt, int learn,int interest,int discip); // Установить показатели работы ученика в заданные значения (для копирования)
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
            QString sex;    // Пол ученика
            int concentr;   // Способность к концентрации
            int humanit;    // Склонность к гуманитарным наукам
            int technical;  // Склонность к техническим наукам
            int ruffian;    // Нарушение дисциплины
            double learn;      // Усвоение материала
            int interest;   // Интерес
            int discip;     // Дисциплина
            int fDiscip;    // Злился ли ученик
            int fIntrst;    // Был ли ученик заинтересован
            void initHints(); // Вычислить начальные значения подсказок состояния уч-в
            void addNegative(int disc);   // Увеличение негатива у ученика
            void subNegative(int deskNum);// Снижение негатива у ученика в зависимости от близости к учителю
            void addLearn();
            void changeIntrst(int creat,int hum,int tech);// Изменить степень заинтересованности ученика уроком
    };
    Student *students;  // Ученики в классе
};

#endif // CLASSROOM_H

