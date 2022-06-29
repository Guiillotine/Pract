#include "stopwatch.h"

Stopwatch::Stopwatch()
{
    timer = new QTimer();
}
void Stopwatch::Start(QLabel *lab)
{
    static int min = 0,sec = 0;
    /*sec = ((labSeconds->text()).remove(0,1)).toInt();
    min = (labMinutes->text()).toInt();
    sec++;
    if (sec == 60)
    {
        min++;
        sec = 0;
    }
    if (min < 10) labMinutes->setText("0" + QString::number(min));
    else labMinutes->setText(QString::number(min));
    if (sec < 10) labSeconds->setText(":0"+QString::number(sec));
    else labSeconds->setText(":"+QString::number(sec));
    if (min == 40) timer->stop();*/
}
