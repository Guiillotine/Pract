#include "studentwin2.h"
#include "ui_studentwin2.h"

studentwin2::studentwin2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studentwin2)
{
    ui->setupUi(this);
    setWindowTitle("Характеристики учеников");
    blank.addFile(":/images/Blank.ico");
    icon.addFile(":/images/pupils.ico");
    setWindowIcon(icon);
    ui->label->setAlignment(Qt::AlignCenter);    // Выравнивание текста по центру
    classR = new ClassRoom();
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
    delete classR;
}

void studentwin2::PrintToLabel(QSlider *slider, QLabel *lab)
{
    lab->setText(QString::number(slider->value()));
}


void studentwin2::FillWin(ClassRoom *cr, int k)
{
    if (cr->students[k*2].getFio()=="Ученик")
    {
        ui->lineEdit->setText("Уч. за партой " + QString::number(k+1) + "-1");   //Назвать ученика согласно номеру парты
        ui->lineEdit_2->setText("Уч. за партой " + QString::number(k+1) + "-2"); //Назвать соседа согласно номеру парты
    }
    else
    {
        ui->lineEdit->setText(cr->students[k*2].getFio());
        ui->lineEdit_2->setText(cr->students[k*2+1].getFio());
    }
    ui->cbSex->setCurrentText(cr->students[k*2].getSex());
    ui->SliderConcentr->setSliderPosition(cr->students[k*2].getConcentr());
    ui->SliderHealth->setSliderPosition(cr->students[k*2].getHealth());
    ui->SliderHumanit->setSliderPosition(cr->students[k*2].getHumanit());
    ui->SliderTechnical->setSliderPosition(cr->students[k*2].getTechnical());
    ui->SliderBad->setSliderPosition(cr->students[k*2].getRuffian());
    ui->cbSex_2->setCurrentText(cr->students[k*2+1].getSex());
    ui->SliderConcentr_2->setSliderPosition(cr->students[k*2+1].getConcentr());
    ui->SliderHealth_2->setSliderPosition(cr->students[k*2+1].getHealth());
    ui->SliderHumanit_2->setSliderPosition(cr->students[k*2+1].getHumanit());
    ui->SliderTechnical_2->setSliderPosition(cr->students[k*2+1].getTechnical());
    ui->SliderBad_2->setSliderPosition(cr->students[k*2+1].getRuffian());
    classR = cr;    // Запомнить адрес объекта
    deskNumber = k; // Запомнить номер выбранной парты
    if (classR->students[30].getSex() != "") // Перемещаемый ученик
    {
        if (classR->students[30].getSex() == "Девочка") ui->label->setText(classR->students[30].getFio() + " выбрана для перемещения");
        else ui->label->setText(classR->students[30].getFio() + " выбран для перемещения");
    }
}

void studentwin2::SetStudents(ClassRoom *cr, int k) // Заполнение полей двух учеников - соседей по парте
{
    cr->students[k*2].setStudent(ui->lineEdit->text(),ui->cbSex->currentText(),ui->SliderHealth->value(),ui->SliderConcentr->value(), ui->SliderHumanit->value(),ui->SliderTechnical->value(),ui->SliderBad->value());
    cr->students[k*2+1].setStudent(ui->lineEdit_2->text(),ui->cbSex_2->currentText(),ui->SliderHealth_2->value(),ui->SliderConcentr_2->value(), ui->SliderHumanit_2->value(),ui->SliderTechnical_2->value(),ui->SliderBad_2->value());
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

void studentwin2::on_bCopy_clicked()
{
    if (classR->students[deskNumber*2].getSex()!= "")
    {
        classR->CopySt(deskNumber*2);// Копировать
        if (classR->students[deskNumber*2].getSex() == "Девочка") ui->label->setText(classR->students[deskNumber*2].getFio() + " выбрана для перемещения");
        else ui->label->setText(classR->students[deskNumber*2].getFio() + " выбран для перемещения");
    }
}

void studentwin2::on_bCopy_2_clicked()
{
    if (classR->students[deskNumber*2+1].getSex()!= "")
    {
        classR->CopySt(deskNumber*2+1);// Копировать
        if (classR->students[deskNumber*2+1].getSex() == "Девочка") ui->label->setText(classR->students[deskNumber*2+1].getFio() + " выбрана для перемещения");
        else ui->label->setText(classR->students[deskNumber*2+1].getFio() + " выбран для перемещения");
    }
}

void studentwin2::on_bPaste_clicked()
{
    if ((classR->students[30].getSex()!= "")&&(classR->students[deskNumber*2].getSex()!= "")) // Если буфер не пуст и есть, с кем меняться
    {
        classR->PasteSt(deskNumber*2);// Вставить
        FillWin(classR,deskNumber); // Заполнить окно новыми данными
        ui->label->setText(classR->students[classR->getBuffStNum()].getFio() + " и " + classR->students[30].getFio() + " поменялись местами");
    }
}

void studentwin2::on_bPaste_2_clicked()
{
    if ((classR->students[30].getSex()!= "")&&(classR->students[deskNumber*2+1].getSex()!= "")) // Если буфер не пуст и есть, с кем меняться
    {
        classR->PasteSt(deskNumber*2+1);// Вставить
        FillWin(classR,deskNumber); // Заполнить окно новыми данными
        ui->label->setText(classR->students[classR->getBuffStNum()].getFio() + " и " + classR->students[30].getFio() + " поменялись местами");
    }
}
