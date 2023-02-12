#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include<QCryptographicHash>
#include<QByteArray>
#include<QString>

SignUpWindow::SignUpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sign Up");
}

SignUpWindow::~SignUpWindow()
{
    delete ui;
}

void SignUpWindow::on_pushButton_SignUp_clicked()
{


    QString username=ui->lineEdit_userName->text();
    QString password=ui->lineEdit_Password->text();
    QString confirmPassword=ui->lineEdit_ConfirmPassword->text();
    QString code=ui->lineEdit_code->text();
    QString code_file;

    QFile codeFile("../final-project-deaddata/DeadData/admins & codes/code.txt");
    if(codeFile.open(QIODevice::ReadOnly)){
    QTextStream ff(&codeFile);
     code_file=ff.readLine();
    codeFile.close();
    }

     if(ui->lineEdit_userName->text().isEmpty() || ui->lineEdit_Password->text().isEmpty() || ui->lineEdit_ConfirmPassword->text().isEmpty() ||ui->lineEdit_code->text().isEmpty() )
     {
         QMessageBox::warning(this,"warning","PLease,Comlpete your data");
     }
     else if(code!=code_file){
         QMessageBox::warning(this,"warning","You can't craete account");
     }
     else
     {

         QFile checkUserName("../final-project-deaddata/DeadData/admins & codes/"+username+".txt");
         if(checkUserName.open(QIODevice::ReadOnly)){
             QMessageBox::warning(this,"warning","This user name is unaviable");
             checkUserName.close();
         }
         else{
             if(password==confirmPassword){
             QByteArray pass_hash = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Sha256);
             QFile f("../final-project-deaddata/DeadData/admins & codes/"+username+".txt");
             if(f.open(QIODevice::WriteOnly)){
             QTextStream s(&f);
             QString hashed = QString(pass_hash);
             s<<username<<"\n"<<hashed;
             f.close();
             hide();
             }
             else{
                 QMessageBox::warning(this,"warning","Can't create account");

             }
             }
             else{
                 QMessageBox::warning(this,"warning","passwords don't match");
             }

         }
     }
}

