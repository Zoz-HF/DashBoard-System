#include "student.h"
#include"course.h"
#include<iostream>
#include<QFile>
#include<vector>
#include<QIODevice>
#include<QFileDialog>

int Student::no_of_students=0;
QMap<QString,Student> Student::students={};

int Student::getNo_of_students()
{
    return no_of_students;
}

QString Student::getId() const
{
    return id;
}

Student::Student():Person(){
    year = "";
    id=QString::number(9210400+no_of_students);
}

Student::Student(QString newFirstName,QString newSecondName,QString newPhoneNumber,
                 QString newEmail,int newAge,QString year):Person(newFirstName, newSecondName, newPhoneNumber, newEmail, newAge)
{
    this->year = year ;
    no_of_students++;
    id=QString::number(9210400+no_of_students);
    students.insert(id,*this);
}

Student::Student(QString newFirstName,QString newSecondName,QString newPhoneNumber,
                 QString newEmail,int newAge,QString year, QMap<QString , float > course_grads):
    Student( newFirstName, newSecondName, newPhoneNumber,newEmail, newAge,year)

{
    this->course_grads=course_grads;
}
void Student::setYear(QString year)
{
    this->year =year;

}
QString Student::getYear() const{
    return year;
}
// -1 means no grad added
void Student::addCourseToStudent(QString c, float year =-1) {

    course_grads.insert(c,year);
}

//delete course from student and delete student from course
// &&waiting course class
void  Student::removeCourseFromStudent(QString c){
    course_grads.remove(c);

}

QMap<QString , float > Student::get_course_grads(){
    return course_grads;
}

void Student::exportToCsvFile(QString path){


    //QFile f("C:/Users/Eng.Habeba/Downloads/Telegram Desktop/latest_dd/csv/students.csv");
    QFile f(path);
    vector<QString> v;
    QTextStream s(&f);
    f.open(QIODevice::WriteOnly|QIODevice::Truncate);

    s<<"FirstName,LastName,Age,Email,PhoneNumber,Year";

    QMap<QString,Course>::Iterator student_courses_it = Course::courses.begin();//code, course
    while(student_courses_it != Course::courses.end()){
       if(student_courses_it == Course::courses.begin()) s<<",";

        s<<student_courses_it.key();
        v.push_back(student_courses_it.key());
        if(student_courses_it != --Course::courses.end()){s<<",";}
        student_courses_it++;
    }
    s<<"\n";

    QMap<QString,Student>::Iterator student_it = Student::students.begin();
    while(student_it != Student::students.end()){

        s<<student_it.value().firstName<<","<<student_it.value().secondName<<","<<student_it.value().getAge()<<","<<student_it.value().getEmail()<<","<<student_it.value().getPhoneNumber()<<","<<student_it.value().getYear()<<",";
        for(int i=0;i<v.size();i++){
            if(student_it->get_course_grads().find(v[i]) != student_it->get_course_grads().end()&&(student_it->get_course_grads().find(v[i]).value()<1000)&&(student_it->get_course_grads().find(v[i]).value()>1)){
                s<<student_it->get_course_grads().find(v[i]).value()<<",";
            }else{s<<"NoGradeYet,";}
        }
        student_it++;
        s<<"\n";
    }

}

void Student::importFromCsvFile(QString path){

    QFile file(path);

    if (file.open(QIODevice::ReadWrite)) {


        //int lineindex = 1;                     // file line counter
        QTextStream in(&file);
        // read to text stream


        while (!in.atEnd()) {


            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            if(!fileLine.startsWith("FirstName", Qt::CaseSensitive)){
            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(',',Qt::SkipEmptyParts);

            // load parsed data to model accordingly

            QString Fname = lineToken.at(0);
            QString Sname =  lineToken.at(1);
            int age = (lineToken.at(2)).toInt();
            QString email = lineToken.at(3);
            QString phone = lineToken.at(4);
            QString titel = lineToken.at(5);
            //0fname, 1sname, 2age, 3email, 4phone, 5year
            Student *p = new Student(Fname,Sname,phone,email,age,titel);

}
          //  lineindex++;
        }

        file.close();
    }


}




