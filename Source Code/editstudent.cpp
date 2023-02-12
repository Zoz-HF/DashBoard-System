#include "editstudent.h"
#include "ui_editstudent.h"
#include "student.h"
#include "studentstab.h"
#include<QMessageBox>
EditStudent::EditStudent(QWidget *parent, QMap<QString,Student>::Iterator st) :
    QWidget(parent),
    ui(new Ui::EditStudent)
{
    ui->setupUi(this);
    setWindowTitle("Edit Student");
    i =st;
    ui->lineEdit_Fname->setText(i.value().getFirstName());
    ui->lineEdit_Sname->setText(i.value().getSecondName());
    ui->lineEdit_age->setText(QString::number(i.value().getAge()));
    ui->lineEdit_email->setText(i.value().getEmail());
    ui->lineEdit_phone->setText(i.value().getPhoneNumber());
    ui->comboBox_grade->setCurrentText(i.value().getYear());

}

EditStudent::~EditStudent()
{
    delete ui;
}


void EditStudent::on_pushButton_addStudent_clicked()
{
    if(ui->lineEdit_Fname->text().isEmpty()||ui->lineEdit_Sname->text().isEmpty()||ui->lineEdit_age->text().isEmpty()||ui->lineEdit_email->text().isEmpty()||ui->lineEdit_phone->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please complete your information!");
    }
    else{

        QString newFName= ui->lineEdit_Fname->text(),
                newSName= ui->lineEdit_Sname->text(),
                newPhone = ui->lineEdit_phone->text(),
                newEmail = ui->lineEdit_email->text(),
                newYear = ui->comboBox_grade->currentText();

        int newAge=ui->lineEdit_age->text().toInt();

        i.value().setFirstName(newFName);
        i.value().setSecondName(newSName);
        i.value().setYear(newYear);
        i.value().setEmail(newEmail);
        i.value().setPhoneNumber(newPhone);
        i.value().setAge(newAge);


        emit edited();
        hide();
    }
}

