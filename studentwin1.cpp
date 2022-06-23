#include "studentwin1.h"
#include "ui_studentwin1.h"

StudentWin1::StudentWin1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWin1)
{
    ui->setupUi(this);
}

StudentWin1::~StudentWin1()
{
    delete ui;
}
