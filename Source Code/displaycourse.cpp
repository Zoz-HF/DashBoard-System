#include "displaycourse.h"
#include "ui_displaycourse.h"
#include <QTableWidgetItem>
#include<QString>
#include<QTableWidget>
#include<QColumnView>
#include <QMessageBox>
//#include <QDoubleValidator>
#include"QComboBox"
#include "editstdgrade.h"
void displayCourse::buildTableOfStudentGrads(){
    QTableWidgetItem *item;

    QMap<QString,float>::const_iterator i = y->getStudents().constBegin();
    while(i != y->getStudents().constEnd())
    {

        ui->tableWidget_student->insertRow (ui->tableWidget_student->rowCount());
        item = new QTableWidgetItem;
        item->setText(Student::students.find(i.key())->get_full_name());
        ui->tableWidget_student->setItem(ui->tableWidget_student->rowCount()-1,0,item);
        item = new QTableWidgetItem;
        item->setData(Qt::EditRole,i.value());
       ui->tableWidget_student->setItem(ui->tableWidget_student->rowCount()-1,1,item);
       item = new QTableWidgetItem;
       item->setData(Qt::EditRole,i.key());
      ui->tableWidget_student->setItem(ui->tableWidget_student->rowCount()-1,2,item);
      i++;
    }
}
void displayCourse::buildTableOfProfessors(){

    QTableWidgetItem *item;
    QSet<QString>::iterator j = y->professors.begin();
     while(j != y->professors.end())
     {
         ui->tableWidget_prof->insertRow (ui->tableWidget_prof->rowCount());
         item = new QTableWidgetItem;
         item->setText(Professor::professors.find(*j)->get_full_name());
         ui->tableWidget_prof->setItem(ui->tableWidget_prof->rowCount()-1,0,item);
         item = new QTableWidgetItem;
         item->setData(Qt::EditRole,*j);
        ui->tableWidget_prof->setItem(ui->tableWidget_prof->rowCount()-1,1,item);
        j++;
     }
}

void displayCourse::buildProfComboBox(bool l)
{
    ui->comboBox_2->addItem("none");
    QMap<QString,Professor>::iterator p =Professor::professors.begin();
    while(p != Professor::professors.end())
   {   if(y->professors.find(p.key())==y->professors.end())
        {
           ui->comboBox_2->addItem(Professor::professors[p.key()].get_full_name());
    if(l) list_prof.push_back(p);
        }
    p++;
    }
}

void displayCourse::buildStudentComboBox(bool l)
{
    ui->comboBox->addItem("none");
    QMap<QString,float> st =y->getStudents();
    QMap<QString,Student>::iterator s =Student::students.begin();
    while(s != Student::students.end())
    {   if(st.find(s.key())==st.end())
        {
           ui->comboBox->addItem(Student::students[s.key()].get_full_name());
   if(l) list_st.push_back(s);
        }
    s++;
    }
}
displayCourse::displayCourse(QWidget *parent,QString code) :
    QWidget(parent),
    ui(new Ui::displayCourse)
{
    y=Course::courses.find(code);
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle("Course info");
    ui->lineEdit->setValidator(new QDoubleValidator(0.0,100.0,3));

    //student table right click menu
        ui->tableWidget_student->setContextMenuPolicy(Qt::ActionsContextMenu);

        QAction *show=new QAction("Show information", this);
    connect(show,SIGNAL(triggered()),this,SLOT(on_show_Clicked()));
    show->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    //ui->tableWidget_student->addAction(show);

    QAction *remove=new QAction("Remove from course", this);
    connect(remove,SIGNAL(triggered()),this,SLOT(on_remove_Clicked()));
    remove->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    ui->tableWidget_student->addAction(remove);

    QAction *deleting=new QAction("Delete", this);
    connect(deleting,SIGNAL(triggered()),this,SLOT(on_delete_Clicked()));
    deleting->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    ui->tableWidget_student->addAction(deleting);

    QAction *edit_grade=new QAction("Edit student's grade", this);
    connect(edit_grade,SIGNAL(triggered()),this,SLOT(on_edit_grade_Clicked()));
    edit_grade->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    ui->tableWidget_student->addAction(edit_grade);

    //professor table right click menu
    ui->tableWidget_prof->setContextMenuPolicy(Qt::ActionsContextMenu);

    //ui->tableWidget_prof->addAction(show);
    ui->tableWidget_prof->addAction(remove);
    ui->tableWidget_prof->addAction(deleting);



    //set label
    ui->label_code->setText(y->getCode());
    ui->label_course->setText(y->getName());
    ui->label_hall->setText(y->getLectureHall());
    ui->label_time->setText(y->getTime());
    //set header for students table
    ui->tableWidget_student->setColumnCount(3);
    ui->tableWidget_student->setColumnHidden(2,true);
    ui->tableWidget_student->setHorizontalHeaderLabels({"name","grade","id"});
    ui->tableWidget_student->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //set header for professors table
    ui->tableWidget_prof->setColumnCount(2);
    ui->tableWidget_prof->setColumnHidden(1,true);
    ui->tableWidget_prof->setHorizontalHeaderLabels({"name","id"});
    ui->tableWidget_prof->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //building combo boxes and tables
    buildTableOfStudentGrads();
    buildTableOfProfessors();
    buildStudentComboBox(true);
    buildProfComboBox(true);

    editCourseWindow=new editCourse(nullptr,y);
    connect(editCourseWindow,SIGNAL(refresh_display_course()),this,SLOT(need_to_refresh()));
}

displayCourse::~displayCourse()
{
    delete ui;
}
void  displayCourse::on_pushButton_add_student_clicked()
{
QString added_student = ui->comboBox->currentText();
if(added_student == "none")
     QMessageBox::warning(nullptr,"Unchosen student","Choose student from list");
else
{
y->addStudent(list_st[ui->comboBox->currentIndex()-1]->getId(),ui->lineEdit->text().toFloat());
list_st[ui->comboBox->currentIndex()-1]->addCourseToStudent(y->getCode(),ui->lineEdit->text().toFloat());
list_st.remove(ui->comboBox->currentIndex()-1);
ui->comboBox->clear();
ui->tableWidget_student->clearContents();
ui->tableWidget_student->setRowCount(0);
buildStudentComboBox(false);
buildTableOfStudentGrads();
ui->lineEdit->clear();
}
}


void displayCourse::on_tableWidget_student_cellDoubleClicked(int row, int column)
{

}


void displayCourse::on_tableWidget_prof_cellDoubleClicked(int row, int column)
{

}




void displayCourse::on_pushButton_editCourse_clicked()
{
    editCourseWindow->buildComboBox();
    editCourseWindow->show();
}

void displayCourse::need_to_refresh(){
    ui->label_course->setText(y->getName());
    ui->label_code->setText(y->getCode());
    ui->label_hall->setText(y->getLectureHall());
    ui->label_time->setText(y->getTime());
    emit refresh();
}

void displayCourse::on_pushButton_add_prof_clicked()
{QString added_prof = ui->comboBox_2->currentText();
    if(added_prof == "none")
         QMessageBox::warning(nullptr,"Unchosen professor","choose professor from list");
    else
    {
    y->addProfessor(list_prof[ui->comboBox_2->currentIndex()-1]->getId());
    list_prof[ui->comboBox_2->currentIndex()-1]->addCourse(y->getCode());
    list_prof.remove(ui->comboBox_2->currentIndex()-1);
    ui->comboBox_2->clear();
    ui->tableWidget_prof->clearContents();
    ui->tableWidget_prof->setRowCount(0);
    buildProfComboBox(false);
    buildTableOfProfessors();
    }
}

void displayCourse::on_remove_Clicked()
{
    QString deleted_id;
    if(!ui->tableWidget_student->selectedItems().isEmpty())
    {
        foreach (QTableWidgetItem* item, ui->tableWidget_student->selectedItems())
    {
        deleted_id=ui->tableWidget_student->item(item->row(),2)->text();
      QMap<QString,Student>::Iterator j=Student::students.find(deleted_id);
j->removeCourseFromStudent(y->getCode());
y->deleteStudent(j->getId());
}
    list_st.clear();
    ui->comboBox->clear();
    ui->tableWidget_student->clearContents();
    ui->tableWidget_student->setRowCount(0);
buildTableOfStudentGrads();
buildStudentComboBox(true);
    }
if(!ui->tableWidget_prof->selectedItems().isEmpty())
{foreach (QTableWidgetItem* item, ui->tableWidget_prof->selectedItems())
    {
        deleted_id=ui->tableWidget_prof->item(item->row(),1)->text();
      QMap<QString,Professor>::Iterator j=Professor::professors.find(deleted_id);
j->removeCourse(y->getCode());
y->deleteProf(j->getId());
}
    list_prof.clear();
    ui->comboBox_2->clear();
    ui->tableWidget_prof->clearContents();
    ui->tableWidget_prof->setRowCount(0);
buildTableOfProfessors();
buildProfComboBox(true);
}
}

void displayCourse::on_delete_Clicked()
{QString deleted_id;
    if(!ui->tableWidget_student->selectedItems().isEmpty())

    {
        foreach (QTableWidgetItem* item, ui->tableWidget_student->selectedItems())
        {
            deleted_id=ui->tableWidget_student->item(item->row(),2)->text();
            QMap<QString,Student>::Iterator j=Student::students.find(deleted_id);


            QMap<QString,float>::ConstIterator c = j->get_course_grads().cbegin();
            while(c!= j->get_course_grads().cend())
            {
                Course::courses.find(c.key())->deleteStudent(deleted_id);
                c++;
            }
            Student::students.remove(deleted_id);
        }
        ui->tableWidget_student->clearContents();
        ui->tableWidget_student->setRowCount(0);
        buildTableOfStudentGrads();
    }
if(!ui->tableWidget_prof->selectedItems().isEmpty())
{
    foreach (QTableWidgetItem* item, ui->tableWidget_prof->selectedItems())
    {
        deleted_id=ui->tableWidget_prof->item(item->row(),1)->text();
        QMap<QString,Professor>::Iterator j=Professor::professors.find(deleted_id);

        QSet<QString>::ConstIterator c = j->getCourses().cbegin();
        while(c!= j->getCourses().cend())
        {
            Course::courses.find(*c)->deleteProf(deleted_id);
            c++;
        }
        Professor::professors.remove(deleted_id);
    }
    ui->tableWidget_prof->clearContents();
    ui->tableWidget_prof->setRowCount(0);
    buildTableOfProfessors();
}
}

void displayCourse::on_edit_grade_Clicked()
{
    if(ui->tableWidget_student->selectedItems().size()!=1)
        QMessageBox::warning(nullptr,"multiple selections","Please choose one student");
    else
    {
    j=Student::students.find(ui->tableWidget_student->item(ui->tableWidget_student->selectedItems()[0]->row(),2)->text());
editStdGrade *edit =new editStdGrade(nullptr,ui->tableWidget_student->item(ui->tableWidget_student->selectedItems()[0]->row(),1)->text().toDouble());
connect(edit,SIGNAL(edit_finished(int)),this,SLOT(edit_grade(int)));
edit->show();
    }
}

void displayCourse::on_show_Clicked()
{
    if(ui->tableWidget_student->selectedItems().size()+ui->tableWidget_prof->selectedItems().size()!=1)
        QMessageBox::warning(nullptr,"multiple selections","Please choose one student/professor");
    else if(ui->tableWidget_student->selectedItems().size()==1)
        on_tableWidget_student_cellDoubleClicked(ui->tableWidget_student->selectedItems()[0]->row(),ui->tableWidget_student->selectedItems()[0]->column());
    else if(ui->tableWidget_prof->selectedItems().size()==1)
        on_tableWidget_prof_cellDoubleClicked(ui->tableWidget_prof->selectedItems()[0]->row(),ui->tableWidget_prof->selectedItems()[0]->column());
}



void displayCourse::edit_grade(int grade)
{
j->addCourseToStudent(ui->label_code->text(),grade);
y->addStudent(j->getId(),grade);
ui->tableWidget_student->clearContents();
ui->tableWidget_student->setRowCount(0);
buildTableOfStudentGrads();
}
