#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QTimer>               // Таймер
#include <QTime>                // Время
#include <QPixmap>              //
#include <QPainter>             //
#include <QIcon>                //
#include <QComboBox>
#include <QMessageBox>
#include <QScrollArea>
#include <QMediaPlayer>         // Плееры для воспроизведения звука
#include <QMediaPlayList>       // Для звука
#include "classroom.h"          // Класс "Классная комната"
#include "studentwin1.h"        // Окно для заполнения одного ученика
#include "studentwin2.h"        // Окно для заполнения двух учеников
#include "human.h"              // Класс "Человек"

class QLabel;
class QPushButton; // Объявление класса для создания виджета-кнопки
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//ClassRoom *classRoom = new ClassRoom(); // Создание глобального объекта - классная комната

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void EditClass(int row, int number); // Редактирование класса на экране: изменение парты с заданным рядом и номером
    void Dragging(QLabel *lab, QPoint *point);  // Перетаскивание мышью парты lab за место с координатами point
    void AddToCounter(int a);                   // Добавить к счётчику доступных для размещения парт a
    QScrollArea *scrollArea;
public slots:
    bool eventFilter(QObject *watched, QEvent *event);
    //void EditClass(int row, int number); // Редактирование класса на экране: изменение парты с заданным рядом и номером
    void tcherGoes();  // Учитель идет
    void BeginLsn();   // Начать урок
    void DeleteAllDesks();// Удалить все парты
    void on_bDel_clicked();
    void on_bExit_clicked();
private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    //ClassRoom classRoom;                // Классная комната
    ClassRoom *classRoom = new ClassRoom();                // Классная комната
    QIcon icon,blank;                   // Иконки
    QPixmap bkgndOp,bkgndCl;            // Задний фон с открытой и закрытой дверью
    QPixmap menu,menu1,menu2,menuDel;   // Меню редактирования класса, элементы меню
    QPixmap crossOff,crossOn;           // Крестик неактивен, активен
    QPixmap tcher1,tcher2,tcher3,tcher4,tcher5,tcher6; // Учитель - ходьба
    QPixmap tcherSits;                  // Учитель сидит
    QPixmap desk1,desk2;                // Одноместная и двухместная парты
    QPalette palette;                   // Для установки заднего фона окна
    QTimer *mainTimer,*timerDrag,*timer2;   // Таймеры
    QTime  *time;                           // Время
    QPoint *point1,*point2,*pointDel;       // Координаты центра некоторых label
    QLabel *labels;                         //
    QLabel *labMenu1, *labMenu2,*labCounter,*labDelete;// Пункты меню: одноместная, двухместная парты и оставшееся кол-во парт
    QLabel *labTcher;                                  // Учитель
    QPushButton *bCont,*bExit,*bDel;                   // Кнопки меню
    QComboBox *cmbbox;
signals:
    void sig(ClassRoom*,int);

};
#endif // MAINWINDOW_H
