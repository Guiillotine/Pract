#include "student.h"

Student::Student()
{
    fio = "";
    health = 50;
    concentr = 50;
    humanit = 50;
    technical = 50;
    ruffian = 50;
}

Student::Student(QString fio, int health, int concentr, int humanit, int technical, int ruffian)
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
