#include "human.h"

Human::Human()
{
    fio = "";
    health = 99;
}

QString Human::getFio()
{
    return fio;
}

int Human::getHealth()
{
    return health;
}
