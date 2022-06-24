#include "studentwin2.h"
#include "ui_studentwin2.h"

studentwin2::studentwin2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studentwin2)
{
    ui->setupUi(this);
    setWindowTitle("Добавление учеников");
    blank.addFile(":/images/Blank.ico");
    icon.addFile(":/images/plus2.ico");
    setWindowIcon(icon);
    connect(ui->SliderConcentr, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderConcentr,ui->label_6);});
    connect(ui->SliderHealth, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderHealth,ui->label_2);});
    connect(ui->SliderHumanit, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderHumanit,ui->label_3);});
    connect(ui->SliderTechnical, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderTechnical,ui->label_4);});
    connect(ui->SliderBad, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderBad,ui->label_5);});
    connect(ui->SliderConcentr_2, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderConcentr_2,ui->label_8);});
    connect(ui->SliderHealth_2, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderHealth_2,ui->label_7);});
    connect(ui->SliderHumanit_2, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderHumanit_2,ui->label_9);});
    connect(ui->SliderTechnical_2, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderTechnical_2,ui->label_10);});
    connect(ui->SliderBad_2, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderBad_2,ui->label_11);});
    ui->SliderConcentr->setSliderPosition(50); ui->SliderConcentr_2->setSliderPosition(50);
    ui->SliderHealth->setSliderPosition(99);   ui->SliderHealth_2->setSliderPosition(99);
    ui->SliderHumanit->setSliderPosition(50);  ui->SliderHumanit_2->setSliderPosition(50);
    ui->SliderTechnical->setSliderPosition(50);ui->SliderTechnical_2->setSliderPosition(50);
}

studentwin2::~studentwin2()
{
    delete ui;
}

void studentwin2::PrintToLabel(QSlider *slider, QLabel *lab)
{
    lab->setText(QString::number(slider->value()));
}

void studentwin2::FillWin(ClassRoom *cr, int k)
{
    if (cr->getFio(k*2)=="Ученик")
    {
        ui->lineEdit->setText("Ученик за партой " + QString::number(k+1) + "-1");   //Назвать ученика согласно номеру парты
        ui->lineEdit_2->setText("Ученик за партой " + QString::number(k+1) + "-2"); //Назвать соседа согласно номеру парты
    }
    else
    {
        ui->lineEdit->setText(cr->getFio(k*2));
        ui->lineEdit_2->setText(cr->getFio(k*2+1));
    }
    ui->cbSex->setCurrentText(cr->getSex(k*2));
    ui->SliderConcentr->setSliderPosition(cr->getStConcentr(k*2));
    ui->SliderHealth->setSliderPosition(cr->getStHealth(k*2));
    ui->SliderHumanit->setSliderPosition(cr->getStHumanit(k*2));
    ui->SliderTechnical->setSliderPosition(cr->getStTechnical(k*2));
    ui->SliderBad->setSliderPosition(cr->getStRuffian(k*2));
    ui->cbSex_2->setCurrentText(cr->getSex(k*2+1));
    ui->SliderConcentr_2->setSliderPosition(cr->getStConcentr(k*2+1));
    ui->SliderHealth_2->setSliderPosition(cr->getStHealth(k*2+1));
    ui->SliderHumanit_2->setSliderPosition(cr->getStHumanit(k*2+1));
    ui->SliderTechnical_2->setSliderPosition(cr->getStTechnical(k*2+1));
    ui->SliderBad_2->setSliderPosition(cr->getStRuffian(k*2+1));
    classR = cr;    // Запомнить адрес объекта
    deskNumber = k; // Запомнить номер выбранной парты
}

void studentwin2::SetStudents(ClassRoom *cr, int k) // Заполнение полей двух учеников - соседей по парте
{
    cr->setStudent(k*2,ui->lineEdit->text(),ui->cbSex->currentText(),ui->SliderHealth->value(),ui->SliderConcentr->value(), ui->SliderHumanit->value(),ui->SliderTechnical->value(),ui->SliderBad->value());
    cr->setStudent(k*2+1,ui->lineEdit_2->text(),ui->cbSex_2->currentText(),ui->SliderHealth_2->value(),ui->SliderConcentr_2->value(), ui->SliderHumanit_2->value(),ui->SliderTechnical_2->value(),ui->SliderBad_2->value());
}

void studentwin2::on_bCancel_clicked()
{
    this->close();
}

void studentwin2::on_bOk_clicked()
{
    if ((ui->lineEdit->text()!="")&&(ui->cbSex->currentText()!="")&&(ui->lineEdit_2->text()!="")&&(ui->cbSex_2->currentText()!=""))
    {
        SetStudents(classR,deskNumber);  // Заполнить параметры ученика и его соседа
        this->close();                   // И закрыть форму
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
