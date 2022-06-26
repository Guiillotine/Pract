#ifndef STUDENTWIN2_H
#define STUDENTWIN2_H
#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QIcon>
#include "mainwindow.h"

namespace Ui {
class studentwin2;
}

class studentwin2 : public QDialog
{
    Q_OBJECT

public:
    explicit studentwin2(QWidget *parent = nullptr);
    ~studentwin2();
    void PrintToLabel(QSlider *slider,QLabel *lab); // Вывести значение слайдера в label
public slots:
    void FillWin(ClassRoom *cr,int k);              // Заполнить окно данными ученика
    void SetStudents(ClassRoom *cr,int k);          // Заполнить поля двух учеников данными из окна
private slots:
    void on_bCancel_clicked();
    void on_bOk_clicked();
private:
    Ui::studentwin2 *ui;
    QIcon icon, blank;
    ClassRoom *classR;
    int deskNumber;
};

#endif // STUDENTWIN2_H
