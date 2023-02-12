#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_students_clicked();

    void on_pushButton_professors_clicked();

    void on_pushButton_courses_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionstudents_triggered();

    void on_actionprofessors_triggered();

    void on_actioncourses_triggered();

    void on_actionstudents_2_triggered();

    void on_actionprofessors_2_triggered();

    void on_actioncourses_2_triggered();

private:
    Ui::MainWindow *ui;
};
#endif// MAINWINDOW_H

