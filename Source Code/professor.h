#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "person.h"
#include <QSet>
class Professor: public Person
{
private:
    QString id;
    QString title;
    QSet<QString> courses;
    static int no_of_professors;
public:
  static  QMap<QString,Professor>professors;
    Professor();
    Professor(QString newFirstName,QString newSecondName,QString newPhoneNumber,QString newEmail,int newAge,QString newTitle);
    Professor(QString newFirstName,QString newSecondName,QString newPhoneNumber,QString newEmail,int newAge,QString newTitle,QSet<QString>newCourses);
    void settitle(const QString &newTitle);
    const QString &getTitle() const;
    void addCourse(QString newCourse);
    void removeCourse(QString removed);
    const QSet<QString> &getCourses() const;
    static void exportToCsvFile(QString path);
    void addToCsvFile();
    static int getNo_of_professors();
    QString getId() const;
    static void importFromCsvFile(QString path);
};

#endif
// PROFESSOR_H
