#include "teatcherwin.h"
#include "ui_teatcherwin.h"

TeatcherWin::TeatcherWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeatcherWin)
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

TeatcherWin::~TeatcherWin()
{
    delete ui;
}

void TeatcherWin::PrintToLabel(QSlider *slider, QLabel *lab)
{
    lab->setText(QString::number(slider->value()));
}

void TeatcherWin::FillWin(ClassRoom *cr)
{
    ui->lineEdit->setText(cr->getTchrFio());
    ui->SliderHealth->setSliderPosition(cr->getTchrHealth());
    ui->SliderComm->setSliderPosition(cr->getTchrComm());
    ui->SliderCreat->setSliderPosition(cr->getTchrCreat());
    ui->SliderStrict->setSliderPosition(cr->getTchrStrict());
    classR = cr;    // Запомнить адрес объекта
}

void TeatcherWin::on_bOk_clicked()
{
    if (ui->lineEdit->text()!="")
    {   // Заполнить параметры учителя
        classR->SetTeatcher(ui->lineEdit->text(),ui->SliderHealth->value(),ui->SliderComm->value(),ui->SliderCreat->value(),ui->SliderStrict->value());
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

void TeatcherWin::on_bCancel_clicked()
{
    this->close();
}
