#include "person.h"

int Person::getAge()
{
    return age;
}

void Person::setAge(int newAge)
{
    age = newAge;
}

 QString &Person::getFirstName()
{
    return firstName;
}

void Person::setFirstName( QString &newFirstName)
{
    firstName = newFirstName;
}

 QString &Person::getSecondName()
{
    return secondName;
}

void Person::setSecondName( QString &newSecondName)
{
    secondName = newSecondName;
}

 QString &Person::getPhoneNumber()
{
    return phoneNumber;
}

void Person::setPhoneNumber( QString &newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
}

 QString &Person::getEmail()
{
    return email;
}

void Person::setEmail( QString &newEmail)
{
    email = newEmail;
}

Person::Person()
{
age=-1;
firstName=secondName=phoneNumber=email="";
}

Person::Person(QString newFirstName, QString newSecondName, QString newPhoneNumber, QString newEmail, int newAge)
{
firstName=newFirstName;
secondName=newSecondName;
phoneNumber=newPhoneNumber;
email=newEmail;
age=newAge;
}

QString Person::get_full_name()
{
return getFirstName()+" "+getSecondName();
}
