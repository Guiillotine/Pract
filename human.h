#ifndef HUMAN_H
#define HUMAN_H
#include <QString>

class Human
{
public:
    Human();
    ~Human();
    QString getFio();
    int getHealth();
protected:
    QString fio;    // ФИО человека
    int health;     // Здоровье
};

#endif // HUMAN_H
