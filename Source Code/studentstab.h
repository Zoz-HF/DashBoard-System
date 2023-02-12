#ifndef STUDENTSTAB_H
#define STUDENTSTAB_H

#include "addstudent.h"
#include <QWidget>
#include "course.h"
#include "student.h"
#include "editstudent.h"
namespace Ui {
class StudentsTab;
}

class StudentsTab : public QWidget
{
    Q_OBJECT

public:

    explicit StudentsTab(QWidget *parent = nullptr);
    ~StudentsTab();

private slots:
    void refresh_clicked();

    void on_pushButton_clicked();

    void on_tableWidgets_students_cellDoubleClicked(int row, int column);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_editingFinished();

    void on_show_clicked();

    void add_to_course(int x);

    void on_delete_clicked();

    void on_pushButton_editstd_clicked();

    void on_remove_Clicked();

    void on_edit_grade_Clicked();

    void edit_grade(int grade);

    void filter_course(int n);



    void on_radioButton_prep_clicked();

    void on_radioButton_first_clicked();

    void on_radioButton_second_clicked();

    void on_radioButton_third_clicked();



    void on_radioButton_forth_clicked();

    void on_radioButton_all_clicked();

private:
    QVector<QAction *> actions;
    void filter();
    void buildTableWithFilters();
    QVector <QString> FCV;
    QSet <QString> FCV1;
    QString code;
    QVector<QMap<QString,Course>::iterator> c;
    void buildTable();
    void buildCourseTable();
    QVector <EditStudent*> stdEdit{1};
        EditStudent *Edited;
    QMap<QString,Student>::Iterator s;
    addStudent* addStudentWindow;
    Ui::StudentsTab *ui;
    QString year;
};

#endif // STUDENTSTAB_H
