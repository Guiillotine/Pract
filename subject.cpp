#include "subject.h"

Subject::Subject()
{
    subjNmbr = 4;
    subjects = new QString[subjNmbr];
    subjects[0] = "Математика";
    subjects[1] = "Русский язык";
    subjects[2] = "История";
    subjects[3] = "География";
    name = "";
    blckbrd = new Blackboard();
}

Subject::~Subject()
{
    delete blckbrd;
    delete[] subjects;
}

QString Subject::getName()
{
    return name;
}

void Subject::setSubj(QString SubjName)
{
    for (int i = 0; i < subjNmbr; i++)
    {
        if (subjects[i] == SubjName)
        {
            name = SubjName; // Математика
            if (i == 0)
            {
                technical = 100;
                humanit = 0;
            }
            if (i == 1) // Русский язык
            {
                technical = 0;
                humanit = 100;
            }
            if (i == 2) // История
            {
                technical = 30;
                humanit = 70;
            }
            if (i == 3) // География
            {
                technical = 50;
                humanit = 50;
            }
            return;
        }
    }
    name = "";
}

void Subject::showBlackboard(QLabel *lab)
{
    blckbrd->ShowSubjName(lab, name);
}

QString Subject::getSubject(int number)
{
    if ((number >= 0)&&(number < subjNmbr))
        return subjects[number];
}

int Subject::getHumanit()
{
    return humanit;
}

int Subject::getTechnical()
{
    return technical;
}

int Subject::getSbjNmbr()
{
    return subjNmbr;
}


Subject::Blackboard::Blackboard()
{
    maths.load(":/images/maths.png");
    russ.load(":/images/russ.png");
    hist.load(":/images/history.png");
    geogr.load(":/images/geography.png");
}

void Subject::Blackboard::ShowSubjName(QLabel *lab, QString SubjName)
{
    lab->show();
    if (SubjName=="Математика")        lab->setPixmap(maths);
    else if (SubjName=="Русский язык") lab->setPixmap(russ);
    else if (SubjName=="История")      lab->setPixmap(hist);
    else if (SubjName=="География")    lab->setPixmap(geogr);
    else lab->hide(); // В случае некорректного названия предмета убрать надпись
}
