#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
using namespace std ;

class Person
{
protected:
    QString firstName,secondName,phoneNumber,email;
    int age;

public:
    Person();
    Person(QString newFirstName,QString newSecondName,QString newPhoneNumber,QString newEmail,int newAge);
    int getAge() ;
    void setAge(int newAge);
     QString &getFirstName() ;
    void setFirstName( QString &newFirstName);
     QString &getSecondName() ;
    void setSecondName( QString &newSecondName);
     QString &getPhoneNumber() ;
    void setPhoneNumber( QString &newPhoneNumber);
     QString &getEmail() ;
    void setEmail( QString &newEmail);
    QString get_full_name();

};

#endif // PERSON_H
