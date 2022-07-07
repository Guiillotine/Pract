#ifndef TEACHERWIN_H
#define TEACHERWIN_H
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class TeacherWin;
}

class TeacherWin : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherWin(QWidget *parent = nullptr);
    ~TeacherWin();
    void FillWin(ClassRoom *cr);
    void PrintToLabel(QSlider *slider, QLabel *lab);
private slots:
    void on_bOk_clicked();
    void on_bCancel_clicked();

private:
    Ui::TeacherWin *ui;
    QIcon icon, blank;
    ClassRoom *classR;
};

#endif // TEACHERWIN_H
