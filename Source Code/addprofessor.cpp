#include "addprofessor.h"
#include "ui_addprofessor.h"
#include <QIntValidator>
#include "professor.h"
#include <QTableWidget>

addprofessor::addprofessor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addprofessor)
{setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    setWindowTitle("Add professor");
    ui->lineEdit_Fname->setPlaceholderText("Enter first name");
    ui->lineEdit_Sname->setPlaceholderText("Enter last name");
    ui->lineEdit_age->setPlaceholderText("Enter age ");
    ui->lineEdit_age->setValidator(new QIntValidator(0,100,this));
    ui->lineEdit_email->setPlaceholderText("Enter email");
    ui->lineEdit_phone->setPlaceholderText("Enter phone number");
    ui->lineEdit_phone->setValidator(new QIntValidator(0,10000000000,this));
    ui->lineEdit_title->setPlaceholderText("Enter title");
    QRegularExpressionValidator *noSpaceValidator= new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+"));
    ui->lineEdit_Fname->setValidator(noSpaceValidator);
    ui->lineEdit_Sname->setValidator(noSpaceValidator);
    ui->lineEdit_title->setValidator(noSpaceValidator);
    QRegularExpressionValidator *validatorPhoneNumber= new QRegularExpressionValidator(QRegularExpression("01\\d{8}[0-9]"));
    ui->lineEdit_phone->setValidator(validatorPhoneNumber);
    noSpaceValidator= new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9@.]+"));
    ui->lineEdit_email->setValidator(noSpaceValidator);

}
addprofessor::~addprofessor()
{
    delete ui;
}

void addprofessor::on_pushButton_clicked()
{
    if(ui->lineEdit_Fname->text().isEmpty()||ui->lineEdit_Sname->text().isEmpty()||ui->lineEdit_age->text().isEmpty(),ui->lineEdit_email->text().isEmpty(),
            ui->lineEdit_phone->text().isEmpty(),ui->lineEdit_title->text().isEmpty()){
        QMessageBox::warning(this,"Error","You must complet the information");
    }
    else{
        if(ui->lineEdit_phone->text().size()!=11){
            QMessageBox::warning(this,"Unvalid number","You must Enter a valid number");
        }
        else{

    QString fname = ui->lineEdit_Fname->text();
   QString sname = ui->lineEdit_Sname->text();
   QString titel = ui->lineEdit_title->text();
   QString email = ui->lineEdit_email ->text();
   QString phone = ui->lineEdit_phone->text();
   int age = ui->lineEdit_age->text().toInt();

Professor *prof=new Professor(fname,sname,phone,email,age,titel);

emit rebuildTable();
close();

//ui->lineEdit_Fname->clear();
//ui->lineEdit_Sname->clear();
//ui->lineEdit_age->clear();
//ui->lineEdit_email->clear();
//ui->lineEdit_phone->clear();
        }
}
}

void addprofessor::on_lineEdit_age_inputRejected()
{
    QMessageBox::warning(this,"Input rejected","Enter numbers");
}

