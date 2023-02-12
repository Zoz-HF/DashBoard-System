#include "studentstab.h"
#include "ui_studentstab.h"
#include"QTableWidget"
#include "addstudent.h"
#include <QSignalMapper>
#include <QMessageBox>
#include"editstudent.h"
#include "QCompleter"
#include"student.h"
#include "editstdgrade.h"
#include "professor.h"
#include <QCheckBox>
void StudentsTab::buildTable(){
    QTableWidgetItem *item;
    ui->tableWidgets_students->clearContents();
    ui->tableWidgets_students->setRowCount(0);

        QTableWidget *x = ui->tableWidgets_students;
        QMap<QString, Student>::const_iterator i = Student::students.constBegin();
            while(i!=Student::students.constEnd()){
                x->insertRow(x->rowCount());

                item = new QTableWidgetItem;
                item->setText(i.key());
                x->setItem(x->rowCount()-1, 0, item);

                item = new QTableWidgetItem;
                item->setText(Student::students.find(i.key())->get_full_name());
                x->setItem(x->rowCount()-1, 1, item);

                item = new QTableWidgetItem;
                item->setData(Qt::EditRole, i.value().getYear());
                x->setItem(x->rowCount()-1, 2, item);
                i++;
            }
}

void StudentsTab::buildCourseTable()
{QTableWidgetItem *item;
    ui->tbl_courses->clearContents();
    ui->tbl_courses->setRowCount(0);
    QMap<QString,float>::ConstIterator i= s->get_course_grads().cbegin();
    while(i!=s->get_course_grads().cend())
    {
       ui->tbl_courses->insertRow(ui->tbl_courses->rowCount());

        item = new QTableWidgetItem;
        item->setText(Course::courses.find(i.key())->getName());
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 0, item);

        item = new QTableWidgetItem;
        item->setData(Qt::EditRole,i.value());
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 1, item);

        item = new QTableWidgetItem;
        item->setText(i.key());
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 2, item);
        i++;

    }
}

StudentsTab::StudentsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentsTab)
{

    ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);
  ui->tbl_courses->setColumnCount(3);
  ui->tbl_courses->setHorizontalHeaderLabels({"course","grade","course code"});
  ui->tbl_courses->setColumnHidden(2,true);
    ui->tbl_courses->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgets_students->setColumnCount(3);
    ui->tableWidgets_students->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    buildTable();
       addStudentWindow =new addStudent();
        ui->tableWidgets_students->setHorizontalHeaderLabels({"ID","Name","Year" });

        ui->tableWidgets_students->setContextMenuPolicy(Qt::ActionsContextMenu);
            QAction *show=new QAction("show information", this);
    show->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    connect(show,SIGNAL(triggered()),this,SLOT(on_show_clicked()));
    ui->tableWidgets_students->addAction(show);
                   actions.resize(Course::courses.size());
                   QSignalMapper* mapper =new QSignalMapper(this);
                   QMap<QString,Course>::iterator i=Course::courses.begin();
                   int j=0;

                   while(i!=Course::courses.end())
                   {
                       c.push_back(i);
                       actions[j]=new QAction ("add to "+i->getName(),this);
                       ui->tableWidgets_students->addAction(actions[j]);
                       connect(actions[j],SIGNAL(triggered()),mapper,SLOT(map()));
                       mapper->setMapping(actions[j],j);
                       i++,j++;
                   }
                   connect(mapper,SIGNAL(mappedInt(int)),this,SLOT(add_to_course(int)));



            connect(addStudentWindow,SIGNAL(r()),this,SLOT(refresh_clicked()));
            QAction *dele=new QAction("Delete", this);
            dele->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
            connect(dele,SIGNAL(triggered()),this,SLOT(on_delete_clicked()));
            ui->tableWidgets_students->addAction(dele);

            ui->tbl_courses->setContextMenuPolicy(Qt::ActionsContextMenu);
            QAction *remove=new QAction("Remove", this);
           remove->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
            connect(remove,SIGNAL(triggered()),this,SLOT(on_remove_Clicked()));
            ui->tbl_courses->addAction(remove);
            QAction *edit_grade=new QAction("Edit grade", this);
            edit_grade->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
            connect(edit_grade,SIGNAL(triggered()),this,SLOT(on_edit_grade_Clicked()));
            ui->tbl_courses->addAction(edit_grade);
            ui->tbl_courses->addAction(dele);
        filter();

}

StudentsTab::~StudentsTab()
{
    delete ui;
}

void StudentsTab::refresh_clicked()
{
buildTable();
if(!ui->lbl_fname->text().isEmpty())
{
    ui->lbl_age->setText(QString::number(s->getAge()));
      ui->lbl_fname->setText(s->getFirstName());
     ui->lbl_lname->setText(s->getSecondName());
     ui->lbl_grade->setText(s->getYear());
     ui->lbl_mail->setText(s->getEmail());
     ui->lbl_phone->setText(s->getPhoneNumber());
}
}



void StudentsTab::on_pushButton_clicked()
{

addStudentWindow->show();
}


void StudentsTab::on_tableWidgets_students_cellDoubleClicked(int row, int column)
{

ui->tbl_courses->clearContents();
ui->tbl_courses->setRowCount(0);

   QTableWidgetItem *item;
    item = ui->tableWidgets_students->QTableWidget::itemAt(0,1);
//    qDebug()<<item->text();
//new
    QString chosen = ui->tableWidgets_students->item(row, 0)->text();
   s =Student::students.find(chosen);

   ui->lbl_age->setText(QString::number(s->getAge()));
     ui->lbl_fname->setText(s->getFirstName());
    ui->lbl_lname->setText(s->getSecondName());
    ui->lbl_grade->setText(s->getYear());
    ui->lbl_mail->setText(s->getEmail());
    ui->lbl_phone->setText(s->getPhoneNumber());
buildCourseTable();

}

void StudentsTab::on_lineEdit_textChanged(const QString &arg1)
{
    if(!ui->lineEdit->text().isEmpty())
    { QStringList list ;
        foreach (QTableWidgetItem* item, ui->tableWidgets_students->findItems(ui->lineEdit->text(),Qt::MatchContains)) {
            list <<item->text();
        }
        QCompleter *complite=new QCompleter(list);
        complite->setCaseSensitivity(Qt::CaseInsensitive);
        complite->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
        ui->lineEdit->setCompleter(complite);
    }
    else
        buildTable();
}


void StudentsTab::on_lineEdit_editingFinished()
{    ui->tableWidgets_students->clearContents();
     ui->tableWidgets_students->setRowCount(0);
    QTableWidgetItem *item;
    QTableWidget *x = ui->tableWidgets_students;
    ui->tableWidgets_students->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QMap<QString, Student>::iterator i = Student::students.begin();
    while(i!=Student::students.end()){
      if(ui->lineEdit->text()==i->get_full_name()||ui->lineEdit->text()==i->getYear())
       {                 x->insertRow(x->rowCount());

          item = new QTableWidgetItem;
          item->setText(i.key());
          x->setItem(x->rowCount()-1, 0, item);

          item = new QTableWidgetItem;
          item->setText(i.value().get_full_name());
          x->setItem(x->rowCount()-1, 1, item);

          item = new QTableWidgetItem;
          item->setData(Qt::EditRole, i.value().getYear());
          x->setItem(x->rowCount()-1, 2, item);}
          i++;

    }
}
void StudentsTab::on_show_clicked(){
if(ui->tableWidgets_students->selectedItems().size()==1)
 on_tableWidgets_students_cellDoubleClicked(ui->tableWidgets_students->selectedItems()[0]->row(),ui->tableWidgets_students->selectedItems()[0]->column());
else
   QMessageBox::warning(nullptr,"Error","Please select one student");
}
void StudentsTab::add_to_course(int x)
{
foreach (QTableWidgetItem* item, ui->tableWidgets_students->selectedItems())
{
    c[x]->addStudent(ui->tableWidgets_students->item(item->row(),0)->text(),000);
    Student::students[ui->tableWidgets_students->item(item->row(),0)->text()].addCourseToStudent(c[x]->getCode(),000);
    if(ui->lbl_fname->text()+" "+ui->lbl_lname->text()==ui->tableWidgets_students->item(item->row(),1)->text())
    buildCourseTable();
}
}

void StudentsTab::on_delete_clicked()
{QString deleted_id;
    if(ui->tbl_courses->selectedItems().size()!=0)
    {
        foreach (QTableWidgetItem* item, ui->tbl_courses->selectedItems())
        {deleted_id=ui->tbl_courses->item(item->row(),2)->text();
            QMap<QString,Course>::Iterator j=Course::courses.find(deleted_id);


            QMap<QString,float>::ConstIterator c1 = j->getStudents().cbegin();
            while(c1!= j->getStudents().cend())
            {
                Student::students.find(c1.key())->removeCourseFromStudent(deleted_id);
                c1++;
            }
            QSet<QString>::ConstIterator p = j->professors.cbegin();
            while(p != j->professors.cend())
            {
                Professor::professors.find(*p)->removeCourse(deleted_id);
                p++;
            }
            for(int i=0;i<c.size();i++)
            if(c[i]->getCode()==deleted_id)
                ui->tableWidgets_students->removeAction(actions[i]);
            Course::courses.remove(deleted_id);
        }
        filter();
        buildCourseTable();
    }
    else if(ui->tableWidgets_students->selectedItems().size()!=0)
    {
        ui->tbl_courses->clearContents();
        ui->tbl_courses->setRowCount(0);
        ui->lbl_age->clear();
        ui->lbl_fname->clear();;
        ui->lbl_lname->clear();;
        ui->lbl_grade->clear();;
        ui->lbl_mail->clear();;
        ui->lbl_phone->clear();;
        foreach (QTableWidgetItem* item, ui->tableWidgets_students->selectedItems())
        {
            deleted_id=ui->tableWidgets_students->item(item->row(),0)->text();
            QMap<QString,Student>::Iterator j=Student::students.find(deleted_id);


            QMap<QString,float>::ConstIterator c = j->get_course_grads().cbegin();
            while(c!= j->get_course_grads().cend())
            {
                Course::courses.find(c.key())->deleteStudent(deleted_id);
                c++;
            }
            Student::students.remove(deleted_id);


        }
        buildTable();
    }
}
void StudentsTab::on_pushButton_editstd_clicked()
{
    if(ui->lbl_fname->text().isEmpty()){
        QMessageBox::warning(this,"Warning","Chosse student from table");

    }
    else{
       stdEdit[0]= new EditStudent(nullptr, s);
        connect(stdEdit[0],SIGNAL(edited()),this,SLOT(refresh_clicked()));
        stdEdit[0]->show();
    }

}

void StudentsTab::on_remove_Clicked()
{
    QString deleted_id;
    foreach (QTableWidgetItem* item, ui->tbl_courses->selectedItems())
    {
        deleted_id=ui->tbl_courses->item(item->row(),2)->text();
      QMap<QString,Course>::Iterator j=Course::courses.find(deleted_id);
s->removeCourseFromStudent(j->getCode());
j->deleteStudent(s->getId());
    }
    buildCourseTable();
}

void StudentsTab::on_edit_grade_Clicked()
{
    if(ui->tbl_courses->selectedItems().size()==1)
    {
     code=ui->tbl_courses->item(ui->tbl_courses->selectedItems()[0]->row(),2)->text();
     editStdGrade *edit =new editStdGrade(nullptr,ui->tbl_courses->item(ui->tbl_courses->selectedItems()[0]->row(),1)->text().toDouble());
    connect(edit,SIGNAL(edit_finished(int)),this,SLOT(edit_grade(int)));
  edit->show();
    }
    else
       QMessageBox::warning(nullptr,"Warning","Please select one course");
}

void StudentsTab::edit_grade(int grade)
{
s->addCourseToStudent(code,grade);
Course::courses.find(code)->addStudent(s->getId(),grade);
buildCourseTable();
}

void StudentsTab::filter_course(int n)
{
    if(FCV1.contains(FCV[n]))
        FCV1.remove(FCV[n]);
      else
        FCV1.insert(FCV[n]);
    buildTableWithFilters();
}

void StudentsTab::buildTableWithFilters()
{
    QTableWidgetItem *item;
    ui->tableWidgets_students->clearContents();
    ui->tableWidgets_students->setRowCount(0);
bool accepted = true;
        QTableWidget *x = ui->tableWidgets_students;
        QMap<QString, Student>::iterator i = Student::students.begin();
            while(i!=Student::students.end()){
                accepted = true;
             QMap<QString,float> c =i->get_course_grads();
                for(QSet<QString>::Iterator j=FCV1.begin();j!=FCV1.end();j++)
                {
                    if(c.find(*j)==c.end())
                    {
                        accepted = false;
                        break;
                    }
                }
                if(i->getYear()!=year&&(ui->radioButton_prep->isChecked()||ui->radioButton_first->isChecked()||ui->radioButton_second->isChecked()||ui->radioButton_third->isChecked()||ui->radioButton_forth->isChecked()))
                    accepted = false;
                if(accepted)
                {
                    x->insertRow(x->rowCount());

                    item = new QTableWidgetItem;
                    item->setText(i.key());
                    x->setItem(x->rowCount()-1, 0, item);

                    item = new QTableWidgetItem;
                    item->setText(Student::students.find(i.key())->get_full_name());
                    x->setItem(x->rowCount()-1, 1, item);

                    item = new QTableWidgetItem;
                    item->setData(Qt::EditRole, i.value().getYear());
                    x->setItem(x->rowCount()-1, 2, item);
                }
                i++;
            }
}




void StudentsTab::on_radioButton_prep_clicked()
{
    year="Prep";
    buildTableWithFilters();
}


void StudentsTab::on_radioButton_first_clicked()
{
    year="First";
    buildTableWithFilters();
}


void StudentsTab::on_radioButton_second_clicked()
{
    year="Second";
    buildTableWithFilters();
}


void StudentsTab::on_radioButton_third_clicked()
{
    year="Third";
    buildTableWithFilters();
}

void StudentsTab::on_radioButton_forth_clicked()
{
    year="Forth";
    buildTableWithFilters();
}

void StudentsTab::filter()
{FCV.clear();
    FCV1.clear();
    QWidget *scrollAreaWidgetContents =new QWidget();
    QCheckBox *a;
    QSignalMapper* m =new QSignalMapper(this);
    QVBoxLayout *lay= new QVBoxLayout(this);
    int n=0;
    for(QMap<QString,Course>::Iterator i=Course::courses.begin();i!=Course::courses.end();i++)
    {
        FCV.push_back(i->getCode());
        a=new QCheckBox(i->getName());
        connect(a,SIGNAL(stateChanged(int)),m,SLOT(map()));
        lay->addWidget(a);
        m->setMapping(a,n);
        n++;
    }
    connect(m,SIGNAL(mappedInt(int)),this,SLOT(filter_course(int)));
   scrollAreaWidgetContents->setLayout(lay);
   ui->scrollArea->setWidget(scrollAreaWidgetContents);
}


void StudentsTab::on_radioButton_all_clicked()
{
    buildTableWithFilters();
}


