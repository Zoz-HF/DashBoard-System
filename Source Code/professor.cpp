#include "professor.h"
#include<QFile>
#include<QIODevice>
#include"course.h"
#include"student.h"
#include<QSet>

int Professor::no_of_professors=0;

QMap<QString,Professor> Professor::professors={};

int Professor::getNo_of_professors()
{
    return no_of_professors;
}

QString Professor::getId() const
{
    return id;
}

Professor::Professor():Person()
{
    title="";
    no_of_professors++;
    id = QString::number(2000+no_of_professors);
    professors.insert(id,*this);
}

Professor::Professor(QString newFirstName,QString newSecondName,QString newPhoneNumber,QString newEmail,int newAge,QString newTitle):
    Person(newFirstName,newSecondName,newPhoneNumber,newEmail,newAge){
    title = newTitle;
    no_of_professors++;
    id=QString::number(2000+no_of_professors);
    professors.insert(id,*this);
}

Professor::Professor(QString newFirstName,QString newSecondName,QString newPhoneNumber,QString newEmail,int newAge,QString newTitle,QSet<QString>newCourses)
    :Professor( newFirstName, newSecondName, newPhoneNumber, newEmail, newAge, newTitle)
{
    courses = newCourses;
}
void Professor::settitle(const QString &newTitle){
    title = newTitle;
}
const QString &Professor::getTitle()const{
    return title;
}
void Professor::addCourse(QString newCourse){
    courses.insert(newCourse);
}
void Professor::removeCourse(QString removed){
    auto a=courses.find(removed);
   if (a!=courses.end())
   courses.erase(a);
}
const QSet<QString> &Professor::getCourses() const{
    return courses;
}
void Professor::addToCsvFile(){

//not the best because it we change all professors who have oldData
}
void Professor::exportToCsvFile(QString path){
    QFile f(path);
    vector<QString> v;
    QTextStream s(&f);
    f.open(QIODevice::WriteOnly|QIODevice::Truncate);
    s<<"FirstName,LastName,Age,Email,PhoneNumber,Title,Courses";

    s<<"\n";

    QMap<QString, Professor>::Iterator prof_it = Professor::professors.begin();
    while(prof_it != Professor::professors.end()){

        s<<prof_it.value().firstName<<","<<prof_it.value().secondName<<","<<prof_it.value().getAge()<<","<<prof_it.value().getEmail()<<","<<prof_it.value().getPhoneNumber()<<","<<prof_it.value().getTitle()<<",";

        QSet<QString>::ConstIterator course_it = prof_it->getCourses().cbegin();
        while(course_it !=prof_it->getCourses().cend()){
            s<<*course_it<<",";
            course_it++;
        }
        prof_it++;
        s<<"\n";
}
}
void Professor::importFromCsvFile(QString path){

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
            Professor *p = new Professor(Fname,Sname,phone,email,age,titel);

}
          //  lineindex++;
        }

        file.close();
    }


}


