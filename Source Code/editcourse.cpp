#include "editcourse.h"
#include "ui_editcourse.h"
#include <qvalidator.h>
#include <QMessageBox>
editCourse::editCourse(QWidget *parent, QMap<QString,Course>::Iterator c) :
    QWidget(parent),
    ui(new Ui::editCourse)
{
    ui->setupUi(this);
    setWindowTitle("Edit Course");
    course = c;
    currentName=course->getName();
    currentcode=course->getCode();
    currentTime=course->getTime();
    currentHall=course->getLectureHall();
    splitedTime=currentTime.split(" ");

    ui->lineEdit_code->setText(currentcode);
    ui->lineEdit_name->setText(currentName);

    buildComboBox();

    QRegularExpressionValidator *noSpaceValidator= new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+"));
    ui->lineEdit_name->setValidator(noSpaceValidator);
    ui->lineEdit_code->setValidator(noSpaceValidator);
}

editCourse::~editCourse()
{
    delete ui;
}


void editCourse::on_pushButton_clicked()
{

    if(ui->lineEdit_code->text().isEmpty()||ui->lineEdit_name->text().isEmpty()){
        QMessageBox::warning(this,"Empty fields","please complete the course data");
    }else{
        QString newTime=ui->comboBox_days->currentText()+" "+ui->comboBox_time->currentText(),
                newName=ui->lineEdit_name->text(),
                newCode=ui->lineEdit_code->text(),
                newHall=ui->comboBox_hall->currentText();

        if(ui->comboBox_time->currentIndex()==5){
            QMessageBox::warning(this,"Unchosen time","The time of the course will not change");
            if(checks()){
                if(currentName!=newName){
                        course->setName(newName);
                        Course::courses_names.remove(currentName);
                        Course::courses_names.insert(newName);
                    }
                if(currentcode!=newCode){
                        course->setCode(newCode);
                        Course::courses_codes.remove(currentcode);
                        Course::courses_codes.insert(newCode);
                        Course::courses.remove(currentcode);
                        Course::courses.insert(newCode,course.value());
                    }

                ui->comboBox_time->clear();
                buildComboBox();
                emit refresh_display_course();
                close();
                }

            }
        else{

            if(checks()){
                if(currentName!=newName){
                        course->setName(newName);
                        Course::courses_names.remove(currentName);
                        Course::courses_names.insert(newName);
                    }
                if(currentcode!=newCode){
                        course->setCode(newCode);
                        Course::courses_codes.remove(currentcode);
                        Course::courses_codes.insert(newCode);
                        Course::courses.remove(currentcode);
                        Course::courses.insert(newCode,course.value());
                    }

                course->setTime(newTime);
                //make current time valid
                QVector<int> dimentions=getTimeIndexes(splitedTime,currentHall);
                Course::setDayHallTime(dimentions[0],dimentions[1],dimentions[2],false);
                //make new not valid
                dimentions=getTimeIndexes(newTime.split(" "),newHall);
                Course::setDayHallTime(dimentions[0],dimentions[1],dimentions[2],true

                        );

                ui->comboBox_time->clear();
                buildComboBox();
                emit refresh_display_course();
                close();

                }


        }
    }
}


void editCourse::buildComboBox(){

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

void editCourse::on_comboBox_hall_currentIndexChanged(int index)
{
    ui->comboBox_time->clear();
    buildComboBox();
}


void editCourse::on_comboBox_days_currentIndexChanged(int index)
{
    ui->comboBox_time->clear();
    buildComboBox();
}

bool editCourse::checks(){

    QString newName=ui->lineEdit_name->text(),
            newCode=ui->lineEdit_code->text();

    if(currentName!=newName || currentcode!=newCode){
        if(currentName!=newName && Course::courses_names.find(newName)!=Course::courses_names.end()){
            QMessageBox::warning(this,"Invalid name","There is already course with this name");
            return false;
        }

        else if(currentcode!=newCode && Course::courses_codes.find(newCode)!=Course::courses_codes.end()){
                QMessageBox::warning(this,"Invalid code","There is already course with this code");
                return false;
        }
    }
    return true;
}

QVector<int> editCourse::getTimeIndexes(QStringList a,QString hall){

    QVector<int> v(3);
    if(a[0]=="Sunday") v[0]=0;
    else if(a[0]=="Monday") v[0]=1;
    else if(a[0]=="Tuesday") v[0]=2;
    else if(a[0]=="Wednesday") v[0]=3;
    else  v[0]=4;

    if(hall=="3201") v[1]=0;
    else if(hall=="1125") v[1]=1;
    else if(hall=="3101") v[1]=2;
    else if(hall=="3102") v[1]=3;
    else  v[1]=4;

    if(a[1]=="08:30-10:00") v[2]=0;
    else if(a[1]=="10:15-11:45") v[2]=1;
    else if(a[1]=="12:15-01:45") v[2]=2;
    else if(a[1]=="02:00-03:30") v[2]=3;
    else  v[2]=4;

    buildComboBox();
    return v;
}
