#include "addstudent.h"
#include "ui_addstudent.h"
#include"student.h"
#include<QString>

addStudent::addStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addStudent)
{
    ui->setupUi(this);
    setWindowTitle("Add Student");
    ui->lineEdit_Fname->setPlaceholderText("Enter first name");
    ui->lineEdit_Sname->setPlaceholderText("Enter last name");
    ui->lineEdit_age->setPlaceholderText("Enter age ");
     ui->lineEdit_age->setValidator(new QIntValidator(0,100,this));
    ui->lineEdit_email->setPlaceholderText("Enter email");
    ui->lineEdit_phone->setPlaceholderText("Enter phone number");
    QRegularExpressionValidator *validatorPhoneNumber= new QRegularExpressionValidator(QRegularExpression("01\\d{8}[0-9]"));
    ui->lineEdit_phone->setValidator(validatorPhoneNumber);
    QRegularExpressionValidator *noSpaceValidator= new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+"));
    ui->lineEdit_Fname->setValidator(noSpaceValidator);
    ui->lineEdit_Sname->setValidator(noSpaceValidator);
    noSpaceValidator= new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9@.]+"));
    ui->lineEdit_email->setValidator(noSpaceValidator);
}

addStudent::~addStudent()
{
    delete ui;
}

void addStudent::on_pushButton_addStudent_clicked()
{
if(ui->lineEdit_Fname->text().isEmpty()||ui->lineEdit_Sname->text().isEmpty()||ui->lineEdit_age->text().isEmpty(),ui->lineEdit_email->text().isEmpty()){

QMessageBox::warning(this,"Error","You must complete the information");
}
    else{
    if(ui->lineEdit_phone->text().size()!=11){
        QMessageBox::warning(this,"Unvalid number","Please enter a valid number");
    }
    else{

        QString st_fname(ui->lineEdit_Fname->text()),
                st_Sname(ui->lineEdit_Sname->text()),
                st_email (ui->lineEdit_email->text()),
                st_phone (ui->lineEdit_phone->text());
        int st_age = ui->lineEdit_age->text().toInt();
        QString st_grade=ui->comboBox_grade->currentText();

        Student* s=new Student(st_fname,st_Sname ,st_phone, st_email,st_age,st_grade);

        emit r();



        ui->lineEdit_Fname->clear();
        ui->lineEdit_Sname->clear();
        ui->lineEdit_age->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_phone->clear();
        close();
    }
}
}

