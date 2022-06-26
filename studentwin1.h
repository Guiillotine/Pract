#ifndef STUDENTWIN1_H
#define STUDENTWIN1_H
#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QIcon>
#include "mainwindow.h"

namespace Ui {
class StudentWin1;
}

class StudentWin1 : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWin1(QWidget *parent = nullptr);
    ~StudentWin1();
    void PrintToLabel(QSlider *slider,QLabel *lab); // Вывести значение слайдера в label
public slots:
    void FillWin(ClassRoom *cr,int k);              // Заполнить окно данными ученика
    void SetStudent(ClassRoom *cr,int k);           // Заполнить поля ученика данными из окна
private slots:
    void on_bCancel_clicked();
    void on_bOk_clicked();
    void on_bCopy_clicked();
    void on_bPaste_clicked();

private:
    Ui::StudentWin1 *ui;
    QIcon icon, blank;
    ClassRoom *classR;
    int deskNumber;
};

#endif // STUDENTWIN1_H
