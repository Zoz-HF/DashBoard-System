#include "mainwindow.h"
#include "coursestab.h"
#include "ui_mainwindow.h"
#include "studentstab.h"
#include "professortab.h"
#include"student.h"
#include"professor.h"
#include"course.h"
#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Dashboard");
    ui->tabWidget_main->setTabBarAutoHide(true);
    on_pushButton_courses_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_students_clicked()

{ui->tabWidget_main->currentWidget()->close();
    ui->tabWidget_main->clear();
    ui->tabWidget_main->addTab(new StudentsTab(),QString("Student Tab").arg(ui->tabWidget_main->count()+1));
}


void MainWindow::on_pushButton_professors_clicked()
{ui->tabWidget_main->currentWidget()->close();
    ui->tabWidget_main->clear();
//ui->tabWidget_preview->setMovable(1);
ui->tabWidget_main->addTab(new Professortab(),QString("Professor Tab").arg(ui->tabWidget_main->count()+1));
}


void MainWindow::on_pushButton_courses_clicked()
{ui->tabWidget_main->currentWidget()->close();
    ui->tabWidget_main->clear();
//ui->tabWidget_preview->clear();
ui->tabWidget_main->addTab(new CoursesTab(),QString("Courses Tab").arg(ui->tabWidget_main->count()+1));
}
void MainWindow::on_pushButton_clicked()
{
    QString p=QFileDialog::getSaveFileName(nullptr,"Choose save location","c:\\","csv file(*.csv)");

    Professor::exportToCsvFile(p);
    Course::export_to_csv(p);
}


void MainWindow::on_pushButton_2_clicked()
{

    //Professor::importFromCsvFile();
    //Student::importFromCsvFile();
    //Course::import_from_csv();
}


void MainWindow::on_actionstudents_triggered()
{
    QString p=QFileDialog::getSaveFileName(nullptr,"Choose save location","c:\\","csv file(*.csv)");
    Student::exportToCsvFile(p);
}


void MainWindow::on_actionprofessors_triggered()
{
    QString p=QFileDialog::getSaveFileName(nullptr,"Choose save location","c:\\","csv file(*.csv)");

    Professor::exportToCsvFile(p);
}


void MainWindow::on_actioncourses_triggered()
{
    QString p=QFileDialog::getSaveFileName(nullptr,"Choose save location","c:\\","csv file(*.csv)");
    Course::export_to_csv(p);
}


void MainWindow::on_actionstudents_2_triggered()
{
    QString p=QFileDialog::getOpenFileName(nullptr,tr("choose students file to open"),"c:\\","csv file(*.csv)");
    Student::importFromCsvFile(p);
    on_pushButton_students_clicked();
}


void MainWindow::on_actionprofessors_2_triggered()
{
    QString p=QFileDialog::getOpenFileName(nullptr,tr("choose professors file to open"),"c:\\","csv file(*.csv)");
    Professor::importFromCsvFile(p);
    on_pushButton_professors_clicked();
}


void MainWindow::on_actioncourses_2_triggered()
{
    QString p=QFileDialog::getOpenFileName(nullptr,tr("choose courses file to open"),"c:\\","csv file(*.csv)");
    Course::import_from_csv(p);
    on_pushButton_courses_clicked();
}

