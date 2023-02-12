#include "course.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
int Course::no_of_courses=0;
QMap<QString,Course> Course::courses={};
bool Course::dayHallTime[5][5][5]={{{false}}};
QSet<QString> Course::courses_names={};
QSet<QString> Course::courses_codes={};
QMap<QString, float> Course::getStudents() const
{
    return students;
}



void Course::setDayHallTime(int d, int h, int t, bool value)
{
    dayHallTime[d][h][t]=value;
}

bool Course::getDayHallTime(int d, int h, int t)
{
    return dayHallTime[d][h][t];
}




Course::Course()
{
name = code= lectureHall = time ="";
no_of_courses++;
courses.insert(code,*this);
courses_codes.insert(code);
courses_names.insert(name);
}

Course::Course(QString newName,QString newCode , QString newLectureHall ,QString newTime ){
name = newName;
lectureHall = newLectureHall;
code = newCode;
time = newTime;
no_of_courses++;
courses.insert(code,*this);
courses_codes.insert(code);
courses_names.insert(name);
}

Course::Course(QString newName,QString newCode , QString newLectureHall ,QString newTime ,
    QMap<QString,float>newStudents,QSet<QString>newProfessors)
    :Course( newName, newCode ,  newLectureHall , newTime ){

    students=newStudents;
    professors=newProfessors;
}

QString Course::getName() const
{
    return name;
}

QString Course::getCode(){
    return code;
}

QString Course::getLectureHall(){
    return lectureHall;
}

QString Course::getTime(){
    return time;
}


void Course::setName(QString newName){
    name= newName;
}

void Course::setLectureHAll(QString newLectureHall){
    lectureHall= newLectureHall;
}

void Course::setCode(QString newCode){
    code= newCode;
}

void Course::setTime(QString newTime){
    time = newTime;
}

void Course::addProfessor(QString profName){
    professors.insert(profName);
}

void Course::addStudent(QString id, float grade){
    students[id]=grade;
}

void Course::deleteStudent(QString id)
{
students.remove(id);
}

int Course::getNumberOfCourses()
{
    return no_of_courses;
}
void Course::export_to_csv(QString path){
        QFile f(path);
        {
            if(f.open(QFile::Truncate|QFile::WriteOnly)){
            QTextStream ss(&f);
            ss<<"CourseName,Code,Time,Hall\n";
            QMap<QString,Course>::Iterator it = Course::courses.begin();
            while(it != Course::courses.end()){
                ss<<it.value().getName()<<","<<it.value().getCode()<<","<<it.value().getTime()<<","<<it.value().getLectureHall()<<"\n";
                it++;
            }
        }
            else{
                QMessageBox(QMessageBox::Warning,"Can't open file", "Try closing the excel sheet");
            }
    }
}


void Course::import_from_csv(QString path){

    QFile file(path);

    if (file.open(QIODevice::ReadWrite)) {


        // file line counter
        QTextStream in(&file);
        // read to text stream


        while (!in.atEnd()) {


            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            if(!fileLine.startsWith("CourseName", Qt::CaseSensitive)){
            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(',',Qt::SkipEmptyParts);

            // load parsed data to model accordingly

            QString name = lineToken.at(0),
                    code = lineToken.at(1),
                    hall = lineToken.at(3),
                    time = lineToken.at(2);

            QStringList timelist = time.split(" ",Qt::SkipEmptyParts);

            int day_index;
            if(timelist.at(0) == "Sunday") day_index=0;
            else if(timelist.at(0) == "Monday") day_index=1;
            else if(timelist.at(0) == "Tuesday") day_index=2;
            else if(timelist.at(0) == "Wednesday") day_index=3;
            else if(timelist.at(0) == "Thursday") day_index=4;
            else{continue;}

            int hall_index;
            if(hall == "3201") hall_index=0;
            else if(hall == "1125") hall_index =1;
            else if(hall == "3101") hall_index =2;
            else if(hall == "3102") hall_index =3;
            else if(hall == "3103") hall_index =4;
            else{continue;}

            int times_index;
            if(timelist.at(1) == "08:30-10:00") times_index=0;
            else if(timelist.at(1) == "10:15-11:45") times_index =1;
            else if(timelist.at(1) == "12:15-01:45") times_index =2;
            else if(timelist.at(1) == "02:00-03:30") times_index =3;
            else if(timelist.at(1) == "03:45-05:15") times_index =4;
            else{continue;}

            if(Course::dayHallTime[day_index][hall_index][times_index]==1) continue;
            else{
                Course::dayHallTime[day_index][hall_index][times_index]=1;
            }
            Course *c = new Course(name, code,hall,time);
}
        }
        file.close();
    }
}

void Course::deleteProf(QString id)
{
    professors.remove(id);
}
