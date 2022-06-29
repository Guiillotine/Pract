#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent)
{
    setParent(parent);
}

MyLabel::MyLabel(QWidget *parent, QPixmap image)
{
    setParent(parent);
    setPixmap(image);
    setGeometry(0,0,image.width(),image.height());

}

void MyLabel::setPos(int x, int y)
{
   xPos = x; yPos = y;
   setGeometry(x,y,this->width(),this->height());
}

