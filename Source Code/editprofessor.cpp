#include "editprofessor.h"
#include "ui_editprofessor.h"
#include <QIntValidator>

editProfessor::editProfessor(QWidget *parent, QMap<QString, Professor>::iterator prof) :
    QWidget(parent),
    ui(new Ui::editProfessor)

{

    ui->setupUi(this);
    setWindowTitle("Edit Professor");
    p=prof;
    ui->lineEdit_Fname->setText(p->getFirstName());
    ui->lineEdit_Sname->setText(p->getSecondName());
    ui->lineEdit_age->setText(QString::number(p->getAge()));
    ui->lineEdit_age->setValidator(new QIntValidator(0,100,this));
    ui->lineEdit_email->setText(p->getEmail());
    ui->lineEdit_phone->setText(p->getPhoneNumber());
    ui->lineEdit_phone->setValidator(new QIntValidator(0,10000000000,this));
    ui->lineEdit_title->setText(p->getTitle());

}

editProfessor::~editProfessor()
{
    delete ui;
}

void editProfessor::on_pushButton_edit_clicked()
{QString s;
if(!ui->lineEdit_Fname->text().isEmpty()||!ui->lineEdit_Sname->text().isEmpty()||!ui->lineEdit_age->text().isEmpty()||!ui->lineEdit_email->text().isEmpty()||!ui->lineEdit_phone->text().isEmpty()||!ui->lineEdit_title->text().isEmpty())
{
    s =ui->lineEdit_Fname->text();
    p->setFirstName(s);
    s=ui->lineEdit_Sname->text();
    p->setSecondName(s);
    s=ui->lineEdit_age->text();
    p->setAge(s.toInt());
    s=ui->lineEdit_title->text();
    p->settitle(s);
    s=ui->lineEdit_phone->text();
    p->setPhoneNumber(s);
    s=ui->lineEdit_email->text();
    p->setEmail(s);

    emit r();
    close();
}
else
QMessageBox::warning(nullptr,"","please complete your data");
}

