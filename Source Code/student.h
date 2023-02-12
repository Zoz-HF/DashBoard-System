#ifndef STUDENT_H
#define STUDENT_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMap>
#include "person.h"

class Student: public Person
{
private:
    // grade to Year
    QString year;
    QMap<QString , float > course_grads ;
    static int no_of_students;
    QString id;


public:
   static QMap<QString,Student>students;
    Student();
    Student(QString newFirstName,QString newSecondName,QString newPhoneNumber,
            QString newEmail,int newAge,QString year);
    Student(QString newFirstName,QString newSecondName,QString newPhoneNumber,
            QString newEmail,int newAge,QString year, QMap<QString , float > course_grads);
    void setYear(QString year);
    QString getYear() const;
    void removeCourseFromStudent(QString c );
    void addCourseToStudent(QString c, float d );
    static int getNo_of_students();
    QString getId() const;
    QMap<QString , float > get_course_grads();
    static void importFromCsvFile(QString path);
    static void exportToCsvFile(QString path);
};

#endif // STUDENT_H
