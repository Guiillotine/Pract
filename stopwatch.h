#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <QTimer>
#include <QLabel>
class Stopwatch
{
public:
    Stopwatch();
    void Start(QLabel *lab);
private:
    QTimer *timer;
};

#endif // STOPWATCH_H
