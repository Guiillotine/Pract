#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "human.h"
#include "subject.h"

class ClassRoom
{
public:
    ClassRoom();
    ~ClassRoom();
    void EditPlan(int row, int number, int value);// Редактирование плана расположения парт
    int GetPlan(int row, int number);// Узнать, какая парта находится в звдвнном ряду на заданном месте
    void CopySt(int numberSt); // Скопировать данные указанного ученика в конец массива учеников (буфер)
    void PasteSt(int numberSt);// Скопировать данные из конца массива учеников (буфера) в указанного ученика
    void StLearning(int numberSt);// Происходящее в процессе обучения с учеником
    void StInitHints(int numberSt);
    void clearStFlags(); // Сбросить флаги для всех студентов
    int getBuffStNum();
    int MaxNegSearch(); // Поиск ученика с максимальным уровнем негатива
    Subject *subject;            // Школьный предмет
    int plan[5][3] = {0};        // План расположения парт в классе
    int BuffStNum;               // Буфер для номера ученика при пересадке
    class Student : public Human // Внутренний класс - ученик
    {
        public:
            Student();
            ~Student();
            void setStudent(QString fio,QString sex,int health,int concentr,int humanit,int technical,int ruffian);
            void DelSt();  // Удалить из списка данные студента с заданным номером
            QString getSex();
            int getConcentr();
            int getHumanit();
            int getTechnical();
            int getRuffian();
            int getLearn();
            int getInterest();
            int getDiscip();
            int getfDiscip();
            void setfDiscip();
            int getfIntrst();
            void setfIntrst();
            void setHints(int learn,int interest,int discip); // Установить показатели работы ученика в заданные значения (для копирования)
            void addNegative(int disc);   // Увеличение негатива у ученика
            void subNegative(int deskNum);// Снижение негатива у ученика в зависимости от близости к учителю
            void addLearn(int deskNum,int comm);
            void changeIntrst(int creat,int hum,int tech);// Изменить степень заинтересованности ученика уроком
            void initHints(); // Вычислить начальные значения подсказок состояния уч-в
            void clearFlags();// Сбросить флаги
        private:
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
    };
    Student *students;           // Ученики в классе
    class Teacher : public Human // Внутренний класс - учитель
    {
        public:
            Teacher();
            ~Teacher();
            void SetTeacher(QString fio,int health,int communication, int creativity, int strictness);
            int getComm();
            int getCreat();
            int getStrict();
        private:
            int communication;// Коммунитативные способности
            int creativity;   // Креативность
            int strictness;   // Строгость
    };
    Teacher *teacher;     // Учитель
};

#endif // CLASSROOM_H

