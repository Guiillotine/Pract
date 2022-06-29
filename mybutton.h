#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>

class MyButton : public QPushButton
{
public:
    MyButton(QWidget *parent);
    MyButton(QWidget *parent, QString text);
    void SetPos(int x, int y);
private:
    int x;      // Позиция по х
    int y;      // Позиция по у
    int width;  // Ширина
    int height; // Высота
};

#endif // MYBUTTON_H
