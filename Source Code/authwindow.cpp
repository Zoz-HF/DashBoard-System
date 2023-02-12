#include "authwindow.h"
#include "ui_authwindow.h"
#include <QPixmap>
#include <signupwindow.h>
#include <QFile>
#include<QCryptographicHash>
#include <QMessageBox>
#include "mainwindow.h"
#include "mainwindow.h"
#include <qvalidator.h>


int isSigned(QString userName,QString password){

    QFile user("../final-project-deaddata/DeadData/admins & codes/"+userName+".txt");
    if(!user.open(QIODevice::ReadOnly))
        return 1;
    else
    {
        QString us,
                pass,
                hashed_pass = QString(QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Sha256));

        QTextStream userStream(&user);

        us=userStream.readLine();
        pass=userStream.readLine();

        user.close();
        if(us==userName&&pass==hashed_pass)
            return 2;
        else
            return 3;
    }

}


AuthWindow::AuthWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    setWindowTitle("Authorization");
    QPixmap pix("../final-project-deaddata/DeadData/Assets/auth_image2.png");
    ui->label_image->setPixmap(pix.scaled(500,385,Qt::KeepAspectRatio));
    QRegularExpressionValidator *noSpaceValidator= new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+"));
    ui->lineEdit_Password->setValidator(noSpaceValidator);
    ui->lineEdit_userName->setValidator(noSpaceValidator);

}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::on_pushButton_SignUp_clicked()
{
    SignUpWindow* a =new SignUpWindow();
    a->show();
}


void AuthWindow::on_pushButton_Login_clicked()
{
    if(ui->lineEdit_userName->text().isEmpty()||ui->lineEdit_Password->text().isEmpty())
    {
        QMessageBox::warning(this,"Incomplete information","Please,Enter your whole data");
    }

    else{
        short val = isSigned(ui->lineEdit_userName->text(),ui->lineEdit_Password->text());
        if (val==1) {
            QMessageBox::warning(this,"Error","You are not registered,sign up Please");
        }
        else if(val==2){
            ui->lineEdit_userName->clear();
            ui->lineEdit_Password->clear();
            MainWindow* w=new MainWindow();
            hide();
            w->show();
        }
        else if(val==3){
            QMessageBox::warning(this,"Error","Wrong password");
        }

    }
}

