#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QKeyEvent>            // Для обработки нажатия клавиш
#include <QLabel>
#include <QTimer>               // Таймер

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    bool eventFilter(QObject *watched, QEvent *event);
    void timerCheck();

private:
    Ui::MainWindow *ui;
    QTimer *timer;                  // Таймер
    QPoint *point;                      // Координаты центра label
};
#endif // MAINWINDOW_H
