#include "editstdgrade.h"
#include "ui_editstdgrade.h"
#include <QDoubleValidator>
#include <QMessageBox>
editStdGrade::editStdGrade(QWidget *parent,double grade) :
    QWidget(parent),
    ui(new Ui::editStdGrade)
{
    ui->setupUi(this);
    setWindowTitle("Edit Student's grade");
    setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEdit_newGrade->setValidator(new QDoubleValidator(0.0,100.0,3));
    this->grade=grade;
    ui->lineEdit_newGrade->setText(QString::number(grade));
}
editStdGrade::~editStdGrade()
{
    delete ui;
}

void editStdGrade::on_pushButton_save_clicked()
{
    if(ui->lineEdit_newGrade->text().isEmpty()){
        QMessageBox::warning(this,"Incomplete data","PLease enter the grade");
    }
    else{
        grade=ui->lineEdit_newGrade->text().toDouble();
    }
    emit edit_finished(grade);
    close();
}

