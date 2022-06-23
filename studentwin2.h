#ifndef STUDENTWIN2_H
#define STUDENTWIN2_H

#include <QDialog>

namespace Ui {
class studentwin2;
}

class studentwin2 : public QDialog
{
    Q_OBJECT

public:
    explicit studentwin2(QWidget *parent = nullptr);
    ~studentwin2();

private:
    Ui::studentwin2 *ui;
};

#endif // STUDENTWIN2_H
