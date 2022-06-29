#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>

class MyLabel : public QLabel
{
public:
    MyLabel(QWidget *parent);
    MyLabel(QWidget *parent,QPixmap image);
    void setPos(int x, int y);
private:
    int xPos; // Позиция по х
    int yPos; // Позиция по у
};

#endif // MYLABEL_H
