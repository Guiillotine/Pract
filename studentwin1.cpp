#include "studentwin1.h"
#include "ui_studentwin1.h"

StudentWin1::StudentWin1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWin1)
{
    ui->setupUi(this);
    setWindowTitle("Характеристики ученика");
    blank.addFile(":/images/Blank.ico");
    icon.addFile(":/images/pupils.ico");
    setWindowIcon(icon);
    ui->label->setAlignment(Qt::AlignCenter); // Выравнивание текста по центру
    classR = new ClassRoom();
    connect(ui->SliderConcentr, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderConcentr,ui->label_6);});
    connect(ui->SliderHealth, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderHealth,ui->label_2);});
    connect(ui->SliderHumanit, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderHumanit,ui->label_3);});
    connect(ui->SliderTechnical, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderTechnical,ui->label_4);});
    connect(ui->SliderBad, &QSlider::valueChanged, [=]() {PrintToLabel(ui->SliderBad,ui->label_5);});
    ui->SliderConcentr->setSliderPosition(50);
    ui->SliderHealth->setSliderPosition(99);
    ui->SliderHumanit->setSliderPosition(50);
    ui->SliderTechnical->setSliderPosition(50);
}

StudentWin1::~StudentWin1()
{
    delete ui;
    delete classR;
}

void StudentWin1::PrintToLabel(QSlider *slider, QLabel *lab)
{
    lab->setText(QString::number(slider->value()));
}


void StudentWin1::FillWin(ClassRoom *cr,int k)
{
    if (cr->students[k*2].getFio()=="Ученик") ui->lineEdit->setText("Уч. за партой " + QString::number(k+1)); //Назвать ученика согласно номеру парты
    else ui->lineEdit->setText(cr->students[k*2].getFio());
    ui->cbSex->setCurrentText(cr->students[k*2].getSex());
    ui->SliderConcentr->setSliderPosition(cr->students[k*2].getConcentr());
    ui->SliderHealth->setSliderPosition(cr->students[k*2].getHealth());
    ui->SliderHumanit->setSliderPosition(cr->students[k*2].getHumanit());
    ui->SliderTechnical->setSliderPosition(cr->students[k*2].getTechnical());
    ui->SliderBad->setSliderPosition(cr->students[k*2].getRuffian());
    classR = cr; // Запомнить адрес объекта
    deskNumber = k; // Запомнить номер выбранной парты
    if (cr->students[30].getSex() != "") // Перемещаемый ученик
    {
        if (cr->students[30].getSex() == "Девочка") ui->label->setText(cr->students[30].getFio() + " выбрана для перемещения");
        else ui->label->setText(cr->students[30].getFio() + " выбран для перемещения");
    }
}

void StudentWin1::SetStudent(ClassRoom *cr,int k)
{
    cr->students[k*2].setStudent(ui->lineEdit->text(),ui->cbSex->currentText(),ui->SliderHealth->value(),ui->SliderConcentr->value(), ui->SliderHumanit->value(),ui->SliderTechnical->value(),ui->SliderBad->value());
}

void StudentWin1::on_bCancel_clicked()
{
    this->close();
}

void StudentWin1::on_bOk_clicked()
{
    if ((ui->lineEdit->text()!="")&&(ui->cbSex->currentText()!=""))
    {
        SetStudent(classR,deskNumber);// Заполнить параметры ученика
        this->close();                // И закрыть форму
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

void StudentWin1::on_bCopy_clicked()
{
    if (classR->students[deskNumber*2].getSex()!= "")
    {
        classR->CopySt(deskNumber*2);// Копировать
        if (classR->students[deskNumber*2].getSex() == "Девочка") ui->label->setText(classR->students[deskNumber*2].getFio() + " выбрана для перемещения");
        else ui->label->setText(classR->students[deskNumber*2].getFio() + " выбран для перемещения");
    }
}

void StudentWin1::on_bPaste_clicked()
{
    if ((classR->students[30].getSex()!= "")&&(classR->students[deskNumber*2].getSex()!= "")) // Если буфер не пуст и есть, с кем меняться
    {
        classR->PasteSt(deskNumber*2);// Вставить
        FillWin(classR,deskNumber); // Заполнить окно новыми данными
        ui->label->setText(classR->students[classR->getBuffStNum()].getFio() + " и " + classR->students[30].getFio() + " поменялись местами");
    }
}
