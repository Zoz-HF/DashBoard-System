#ifndef EDITSTDGRADE_H
#define EDITSTDGRADE_H

#include <QWidget>

namespace Ui {
class editStdGrade;
}

class editStdGrade : public QWidget
{
    Q_OBJECT
signals:
    void edit_finished(int);
public:

    explicit editStdGrade(QWidget *parent = nullptr,double grade=0);
    ~editStdGrade();

private slots:
    void on_pushButton_save_clicked();

private:
    double grade;
    Ui::editStdGrade *ui;
};

#endif // EDITSTDGRADE_H
