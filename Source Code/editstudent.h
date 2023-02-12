#ifndef EDITSTUDENT_H
#define EDITSTUDENT_H

#include <QWidget>
#include "student.h"
namespace Ui {
class EditStudent;
}

class EditStudent : public QWidget
{
    Q_OBJECT

public:
    explicit EditStudent(QWidget *parent = nullptr, QMap<QString,Student>::Iterator st=Student::students.begin());

    ~EditStudent();
signals:
    void edited();
private slots:


    void on_pushButton_addStudent_clicked();

private:
    QMap<QString,Student>::Iterator i;
    Ui::EditStudent *ui;

};

#endif // EDITSTUDENT_H
