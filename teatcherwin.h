#ifndef TEATCHERWIN_H
#define TEATCHERWIN_H

#include <QDialog>

namespace Ui {
class TeatcherWin;
}

class TeatcherWin : public QDialog
{
    Q_OBJECT

public:
    explicit TeatcherWin(QWidget *parent = nullptr);
    ~TeatcherWin();

private:
    Ui::TeatcherWin *ui;
};

#endif // TEATCHERWIN_H
