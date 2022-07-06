#ifndef HUMAN_H
#define HUMAN_H
#include <QString>

class Human
{
public:
    Human();
    QString fio;    // ФИО человека
    int health;     // Здоровье
    QString getFio();
    int getHealth();
private:
};

#endif // HUMAN_H
