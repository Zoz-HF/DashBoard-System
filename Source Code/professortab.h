#ifndef PROFESSORTAB_H
#define PROFESSORTAB_H
#include "addprofessor.h"
#include "professor.h"
#include <QDialog>
#include "course.h"
#include "editprofessor.h"


namespace Ui {
class Professortab;
}

class Professortab : public QDialog
{
    Q_OBJECT

public:
    explicit Professortab(QWidget *parent = nullptr);
    ~Professortab();


private slots:
    void rebuildProfTable();
    void on_pushButton_clicked();

    void on_tableWidgets_prof_cellDoubleClicked(int row, int column);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_editingFinished();

    void on_show_clicked();

    void add_to_course(int x);

    void on_delete_clicked();

    void on_remove_clicked();

    void on_pushButton_editprof_clicked();

private:
    QVector<QAction *> actions;
    void showProfInfo(QString id);
     void buildProfTable();
     void buildCourseTable();
     QMap<QString, Professor>::iterator p;
    QVector<QMap<QString,Course>::iterator> c;
     QVector<addprofessor*> addprof{1};
     QVector<editProfessor*>editprof{1};
    Ui::Professortab *ui;
};

#endif // PROFESSORTAB_H
