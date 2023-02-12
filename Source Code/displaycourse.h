#ifndef DISPLAYCOURSE_H
#define DISPLAYCOURSE_H
#include"course.h"
#include"student.h"
#include"professor.h"
#include <QWidget>
#include "editcourse.h"


namespace Ui {
class displayCourse;
}

class displayCourse : public QWidget
{
    Q_OBJECT
signals:
   void refresh();
public:
    explicit displayCourse(QWidget *parent = nullptr,QString code="");
    ~displayCourse();
QMap<QString,Course>::Iterator y;

private slots:

    void on_pushButton_add_student_clicked();

    void on_tableWidget_student_cellDoubleClicked(int row, int column);

    void on_tableWidget_prof_cellDoubleClicked(int row, int column);

    void need_to_refresh();

    void on_pushButton_editCourse_clicked();

    void on_pushButton_add_prof_clicked();

    void on_remove_Clicked();

    void on_delete_Clicked();

    void on_edit_grade_Clicked();

    void on_show_Clicked();

    void edit_grade(int grade);

private:
    QMap<QString,Student>::Iterator j;
    editCourse *editCourseWindow;
    QVector<QMap<QString,Student>::iterator> list_st;
    QVector<QMap<QString,Professor>::iterator> list_prof;
    Ui::displayCourse *ui;
    void buildTableOfStudentGrads();
    void buildTableOfProfessors();
    void buildProfComboBox(bool l);
    void buildStudentComboBox(bool l);
};

#endif // DISPLAYCOURSE_H
