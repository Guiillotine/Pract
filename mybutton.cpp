#include "mybutton.h"

MyButton::MyButton(QWidget *parent)
{
    setParent(parent);
    width = 221;
    height = 65;
    x = 0, y = 0;
    setMinimumSize(width, height);
    setFont(QFont("Franklin Gothic Demi Cond", 20));       // Установить шрифт кнопки
    setStyleSheet("QPushButton {background-color: #ffeb7c; color: #d5950b;}");
}

MyButton::MyButton(QWidget *parent, QString text)
{
    setParent(parent);
    width = 221;
    height = 65;
    setMinimumSize(width, height);
    setFont(QFont("Franklin Gothic Demi Cond", 20));       // Установить шрифт кнопки
    setStyleSheet("QPushButton {background-color: #ffeb7c; color: #d5950b;}");
    setText(text);
}

void MyButton::SetPos(int x, int y)
{
    this->x = x; this->y = y;
    setGeometry(x,y,width,height);
}
