#include "studentwin2.h"
#include "ui_studentwin2.h"

studentwin2::studentwin2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studentwin2)
{
    ui->setupUi(this);
}

studentwin2::~studentwin2()
{
    delete ui;
}
