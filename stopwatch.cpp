#include "stopwatch.h"

Stopwatch::Stopwatch(QTimer *timer,QLabel *labMinutes,QLabel *labSeconds)
{
    this->timer = new QTimer();
    labMin = new QLabel();
    labSec = new QLabel();
    this->timer = timer;
    labMin = labMinutes;
    labSec = labSeconds;
    min = 0;
    sec = 0;
}

Stopwatch::~Stopwatch()
{

}
void Stopwatch::Start()
{
    sec = ((labSec->text()).remove(0,1)).toInt();
    min = (labMin->text()).toInt();
    sec++;
    if (sec == 60) incMin();
    FormatTime();
}

void Stopwatch::Stop()
{
    min = 0;
    sec = 0;
    timer->stop();
}

void Stopwatch::incMin()
{
    min++;
    sec = 0;
}

void Stopwatch::FormatTime()
{
    if (min < 10) labMin->setText("0" + QString::number(min));
    else labMin->setText(QString::number(min));
    if (sec < 10) labSec->setText(":0"+QString::number(sec));
    else labSec->setText(":"+QString::number(sec));
}

int Stopwatch::getMinutes()
{
    return min;
}

int Stopwatch::getSeconds()
{
    return sec;
}
