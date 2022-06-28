#ifndef TEATCHERWIN_H
#define TEATCHERWIN_H
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class TeatcherWin;
}

class TeatcherWin : public QDialog
{
    Q_OBJECT

public:
    explicit TeatcherWin(QWidget *parent = nullptr);
    ~TeatcherWin();
    void FillWin(ClassRoom *cr);
    void PrintToLabel(QSlider *slider, QLabel *lab);
private slots:
    void on_bOk_clicked();

    void on_bCancel_clicked();

private:
    Ui::TeatcherWin *ui;
    QIcon icon, blank;
    ClassRoom *classR;
};

#endif // TEATCHERWIN_H
