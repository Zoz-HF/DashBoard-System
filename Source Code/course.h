#ifndef COURSE_H
#define COURSE_H
#include <QString>
#include <QObject>
#include <QWidget>
#include <QSet>
#include <QMap>


class Course

{
private:
    QString name,code,lectureHall,time;

    static int no_of_courses;
    QMap<QString, float> students;
    static bool dayHallTime[5][5][5];

public:
    static void setDayHallTime(int d,int h,int t,bool value);
    static bool getDayHallTime(int d,int h,int t);
    QSet<QString> professors;
    static QMap<QString,Course> courses;
    static QSet<QString> courses_names;
    static QSet<QString> courses_codes;
    Course();
    Course(QString newName,QString newCode , QString newLectureHall ,QString newTime );
    Course(QString newName,QString newCode , QString newLectureHall ,QString newTime ,QMap<QString,float>newStudents,QSet<QString>newProfessors);
    QString getName() const;
    void setName(QString newName);
    QString getCode();
    void setCode(QString newCode);
    QString getLectureHall();
    void setLectureHAll(QString newLectureHall);
    QString getTime();
    void setTime(QString newTime);
    void addProfessor(QString profName);
    void addStudent(QString id, float grade);
    void deleteStudent (QString id);
    int getNumberOfCourses();
    QMap<QString, float> getStudents() const;
    static void export_to_csv(QString path);
        static void import_from_csv(QString path);
       void deleteProf(QString id);
};

#endif // COURSE_H
