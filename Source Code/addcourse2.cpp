#include "addcourse2.h"
#include "ui_addcourse2.h"
#include "course.h"
#include <QMessageBox>
addcourse2::addcourse2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addcourse2)
{
    ui->setupUi(this);
    setWindowTitle("Add Course");


buildComboBox();
QRegularExpressionValidator *noSpaceValidator= new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+"));
ui->lineEdit_name->setValidator(noSpaceValidator);
ui->lineEdit_code->setValidator(noSpaceValidator);
}

addcourse2::~addcourse2()
{
    delete ui;
}

void addcourse2::on_pushButton_clicked()
{

    if(ui->lineEdit_code->text().isEmpty()||ui->lineEdit_name->text().isEmpty()){
        QMessageBox::warning(this,"Empty fields","please complete the course data");
    }else{
        if(ui->comboBox_time->currentIndex()==5){
            QMessageBox::warning(this,"Unchosen time","please choose course's time");
        }
        else{
            if(Course::courses_names.find(ui->lineEdit_name->text())!=Course::courses_names.end())
            {
                QMessageBox::warning(this,"Invalid name","there is already course with this name");
            }
            else if(Course::courses_codes.find(ui->lineEdit_code->text())!=Course::courses_codes.end())
            {
                QMessageBox::warning(this,"Invalid code","there is already course with this code");
            }
            else{
                emit button(ui->lineEdit_name->text(),ui->lineEdit_code->text());
                QString t=ui->comboBox_days->currentText()+" "+ui->comboBox_time->currentText();
                Course *c=new Course(ui->lineEdit_name->text(),ui->lineEdit_code->text(),
                ui->comboBox_hall->currentText(),t);
                Course::setDayHallTime(ui->comboBox_days->currentIndex(),ui->comboBox_hall->currentIndex(),ui->comboBox_time->currentIndex(),true);
                ui->comboBox_time->clear();
                ui->lineEdit_name->clear();
                ui->lineEdit_code->clear();
                buildComboBox();
                close();
    }
}
}
}



void addcourse2::buildComboBox(){
    ui->comboBox_time->clear();
    QString times[5]={"08:30-10:00","10:15-11:45","12:15-01:45","02:00-03:30","03:45-05:15"};
    int d=ui->comboBox_days->currentIndex();
    int h=ui->comboBox_hall->currentIndex();

    for(int i=0;i<5;i++){
            ui->comboBox_time->addItem(times[i]);
           if(Course::getDayHallTime(d,h,i))
           {
               ui->comboBox_time->setItemData(i,false,Qt::UserRole-1);
               ui->comboBox_time->setItemData(i, QColor( Qt::gray ), Qt::BackgroundRole );
           }


    }
    ui->comboBox_time->addItem("None");
    ui->comboBox_time->setCurrentIndex(5);
}

void addcourse2::on_comboBox_hall_currentIndexChanged(int index)
{
    ui->comboBox_time->clear();
    buildComboBox();
}



void addcourse2::on_comboBox_days_currentIndexChanged(int index)
{
    ui->comboBox_time->clear();
    buildComboBox();
}




