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

}

QString Subject::getName()
{
    return name;
}

void Subject::setName(QString SubjName)
{
    for (int i = 0; i < subjNmbr; i++)
    {
        if (subjects[i] == SubjName)
        {
            name = SubjName;
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
