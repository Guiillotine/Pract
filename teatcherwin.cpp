#include "teatcherwin.h"
#include "ui_teatcherwin.h"

TeatcherWin::TeatcherWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeatcherWin)
{
    ui->setupUi(this);
}

TeatcherWin::~TeatcherWin()
{
    delete ui;
}
