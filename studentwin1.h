#ifndef STUDENTWIN1_H
#define STUDENTWIN1_H

#include <QDialog>

namespace Ui {
class StudentWin1;
}

class StudentWin1 : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWin1(QWidget *parent = nullptr);
    ~StudentWin1();

private:
    Ui::StudentWin1 *ui;
};

#endif // STUDENTWIN1_H
