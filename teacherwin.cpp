#include "teacherwin.h"
#include "ui_teacherwin.h"

TeacherWin::TeacherWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherWin)
{
    ui->setupUi(this);
    setWindowTitle("Характеристики учителя");
    blank.addFile(":/images/Blank.ico");
    icon.addFile(":/images/teacher.ico");
    setWindowIcon(icon);
    classR = new ClassRoom();
    connect(ui->SliderHealth, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderHealth,ui->label_1);});
    connect(ui->SliderComm, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderComm,ui->label_2);});
    connect(ui->SliderCreat, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderCreat,ui->label_3);});
    connect(ui->SliderStrict, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderStrict,ui->label_4);});
    ui->SliderHealth->setSliderPosition(99);
    ui->SliderComm->setSliderPosition(50);
    ui->SliderCreat->setSliderPosition(50);
    ui->SliderStrict->setSliderPosition(50);
}

TeacherWin::~TeacherWin()
{
    delete ui;
    delete classR;
}

void TeacherWin::PrintToLabel(QSlider *slider, QLabel *lab)
{
    lab->setText(QString::number(slider->value()));
}

void TeacherWin::FillWin(ClassRoom *cr)
{
    ui->lineEdit->setText(cr->teacher->getFio());
    ui->SliderHealth->setSliderPosition(cr->teacher->getHealth());
    ui->SliderComm->setSliderPosition(cr->teacher->getComm());
    ui->SliderCreat->setSliderPosition(cr->teacher->getCreat());
    ui->SliderStrict->setSliderPosition(cr->teacher->getStrict());
    classR = cr;    // Запомнить адрес объекта
}

void TeacherWin::on_bOk_clicked()
{
    if (ui->lineEdit->text()!="")
    {   // Заполнить параметры учителя
        classR->teacher->SetTeacher(ui->lineEdit->text(),ui->SliderHealth->value(),ui->SliderComm->value(),ui->SliderCreat->value(),ui->SliderStrict->value());
        this->close();   // Закрыть форму
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(" ");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Заполнены не все поля");
        msgBox.setWindowIcon(blank);
        msgBox.exec();
    }
}

void TeacherWin::on_bCancel_clicked()
{
    this->close();
}
