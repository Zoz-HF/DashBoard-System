#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QWidget>

namespace Ui {
class addStudent;
}

class addStudent : public QWidget
{
    Q_OBJECT
signals:
    void r();
public:
    explicit addStudent(QWidget *parent = nullptr);
    ~addStudent();

private slots:

    void on_pushButton_addStudent_clicked();

private:
    Ui::addStudent *ui;
};

#endif // ADDSTUDENT_H
