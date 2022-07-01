#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <QTimer>
#include <QLabel>

class Stopwatch
{
public:
    Stopwatch(QTimer *timer, QLabel *labMinutes,QLabel *labSeconds);
    ~Stopwatch();
public slots:
    void Start();
    void Stop();
    void incMin();
    void FormatTime();
    int getMinutes();
private:
    QTimer *timer;  // Адрес таймера
    QLabel *labMin; // Для хранения адресов
    QLabel *labSec; // labels для минут и секунд
    int min;
    int sec;
};

#endif // STOPWATCH_H
