#include "human.h"

Human::Human()
{
    fio = "";
    health = 99;
}

Human::~Human()
{

}

QString Human::getFio()
{
    return fio;
}

int Human::getHealth()
{
    return health;
}
