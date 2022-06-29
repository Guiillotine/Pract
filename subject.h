#ifndef SUBJECT_H
#define SUBJECT_H
#include <QString>
#include <QLabel>
class QLabel;
class Subject
{
public:
    Subject();
    ~Subject();
    QString getName();
    void setName(QString SubjName);
    void showBlackboard(QLabel *lab);
    QString getSubject(int number);
    int getSbjNmbr();
private:
    QString name;
    int humanit;    // Содержание гуманитарных наук в предмете
    int technical;  // Содержание технических наук в предмете
    int subjNmbr;   // Количество наименований предметов
    class Blackboard// Внутренний класс - доска
    {
        public:
            Blackboard();
            QPixmap maths,russ,hist,geogr;
            void ShowSubjName(QLabel *lab, QString SubjName);
    };
    Blackboard *blckbrd; // Школьная доска
    QString *subjects;   // Все предметы
};

#endif // SUBJECT_H
