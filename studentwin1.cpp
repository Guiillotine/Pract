#include "studentwin1.h"
#include "ui_studentwin1.h"

StudentWin1::StudentWin1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentWin1)
{
    ui->setupUi(this);
    setWindowTitle("Добавление ученика");
    blank.addFile(":/images/Blank.ico");
    icon.addFile(":/images/plus2.ico");
    setWindowIcon(icon);
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
}

void StudentWin1::PrintToLabel(QSlider *slider, QLabel *lab)
{
    lab->setText(QString::number(slider->value()));
}


void StudentWin1::FillWin(ClassRoom *cr,int k)
{
    if (cr->getFio(k*2)=="Ученик") ui->lineEdit->setText("Ученик за партой " + QString::number(k+1)); //Назвать ученика согласно номеру парты
    else ui->lineEdit->setText(cr->getFio(k*2));
    ui->cbSex->setCurrentText(cr->getSex(k*2));
    ui->SliderConcentr->setSliderPosition(cr->getStConcentr(k*2));
    ui->SliderHealth->setSliderPosition(cr->getStHealth(k*2));
    ui->SliderHumanit->setSliderPosition(cr->getStHumanit(k*2));
    ui->SliderTechnical->setSliderPosition(cr->getStTechnical(k*2));
    ui->SliderBad->setSliderPosition(cr->getStRuffian(k*2));
    classR = cr; // Запомнить адрес объекта
    deskNumber = k; // Запомнить номер выбранной парты
}

void StudentWin1::SetStudent(ClassRoom *cr,int k)
{
    cr->setStudent(k*2,ui->lineEdit->text(),ui->cbSex->currentText(),ui->SliderHealth->value(),ui->SliderConcentr->value(), ui->SliderHumanit->value(),ui->SliderTechnical->value(),ui->SliderBad->value());
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
