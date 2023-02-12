#include "professortab.h"
#include "ui_professortab.h"
#include "addprofessor.h"
#include <QCompleter>
#include <QSignalMapper>
#include "student.h"
void Professortab::buildProfTable(){
//addProfWindow=new addprofessor();
//   addprof[0]=new addprofessor();
    ui->tableWidgets_prof->clearContents();
    ui->tableWidgets_prof->setRowCount(0);
    QTableWidgetItem *item;
    QTableWidget *x = ui->tableWidgets_prof;
    //ui->tableWidgets_prof->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
QMap<QString, Professor>::iterator j;
    QMap<QString, Professor>::iterator i = Professor::professors.begin();
    while(i!=Professor::professors.end()){
        x->insertRow(x->rowCount());
     j = Professor::professors.find(i.key());
        item = new QTableWidgetItem;
        item->setText(j->get_full_name());
        ui->tableWidgets_prof->setItem(ui->tableWidgets_prof->rowCount()-1,0,item);
        item = new QTableWidgetItem;
        item->setText(j->getTitle());
        ui->tableWidgets_prof->setItem(ui->tableWidgets_prof->rowCount()-1,1,item);
        item = new QTableWidgetItem;
        item->setText(i.key());
        ui->tableWidgets_prof->setItem(ui->tableWidgets_prof->rowCount()-1,2,item);
        i++;
    }
}

void Professortab::buildCourseTable()
{
    ui->tbl_courses->clearContents();
    ui->tbl_courses->setRowCount(0);
        QTableWidgetItem *item;
        QSet<QString>::ConstIterator i= p->getCourses().cbegin();
        while(i!=p->getCourses().cend())
        {
           ui->tbl_courses->insertRow(ui->tbl_courses->rowCount());

            item = new QTableWidgetItem;
            item->setText(Course::courses.find(*i)->getName());
            ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 0, item);
            item = new QTableWidgetItem;
            item->setText(*i);
            ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 1, item);
            i++;

        }
}

Professortab::Professortab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Professortab)
{

    ui->setupUi(this);
setAttribute(Qt::WA_DeleteOnClose);
 addprof[0]=new addprofessor();
ui->tbl_courses->setColumnCount(2);
ui->tbl_courses->setHorizontalHeaderLabels({"course","course code"});
ui->tbl_courses->setColumnHidden(1,true);
  ui->tbl_courses->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

           actions.resize(Course::courses.size());
           QSignalMapper* mapper =new QSignalMapper(this);
           QMap<QString,Course>::iterator i=Course::courses.begin();
           int j=0;

           while(i!=Course::courses.end())
           {
               c.push_back(i);
               actions[j]=new QAction ("add to "+i->getName(),this);
              ui->tableWidgets_prof->addAction(actions[j]);
               connect(actions[j],SIGNAL(triggered()),mapper,SLOT(map()));
              mapper->setMapping(actions[j],j);
               i++,j++;
           }
           connect(mapper,SIGNAL(mappedInt(int)),this,SLOT(add_to_course(int)));

           ui->tableWidgets_prof->setContextMenuPolicy(Qt::ActionsContextMenu);

           QAction *show=new QAction("show information", this);
           show->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
           connect(show,SIGNAL(triggered()),this,SLOT(on_show_clicked()));
           ui->tableWidgets_prof->addAction(show);

           QAction *dele=new QAction("delete", this);
           dele->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
           connect(dele,SIGNAL(triggered()),this,SLOT(on_delete_clicked()));
           ui->tableWidgets_prof->addAction(dele);

    ui->tableWidgets_prof->setColumnCount(3);
    ui->tableWidgets_prof->setHorizontalHeaderLabels({"Name","title","id" });
    ui->tableWidgets_prof->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgets_prof->setColumnHidden(2,true);
    buildProfTable();


    connect(addprof[0],SIGNAL(rebuildTable()),this,SLOT(rebuildProfTable()));
    ui->tbl_courses->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *remove=new QAction("remove", this);
    remove->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    ui->tbl_courses->addAction(remove);
    ui->tbl_courses->addAction(dele);
    connect(remove,SIGNAL(triggered()),this,SLOT(on_remove_clicked()));

}

Professortab::~Professortab()
{
    delete ui;
}

void Professortab::on_pushButton_clicked()
{
    addprof[0]->setModal(true);
    addprof[0]->exec();
}

void Professortab::rebuildProfTable(){
     addprof[0]=new addprofessor();
     connect(addprof[0],SIGNAL(rebuildTable()),this,SLOT(rebuildProfTable()));
//    ui->tableWidgets_prof->clearContents();
//    ui->tableWidgets_prof->setRowCount(0);
    buildProfTable();
    if(!ui->lbl_fname->text().isEmpty())
    {
        ui->lbl_fname->setText(p->getFirstName());
        ui->lbl_lname->setText(p->getSecondName());
        ui->lbl_age->setText(QString::number(p->getAge()));
        ui->lbl_title->setText(p->getTitle());
        ui->lbl_mail->setText(p->getEmail());
        ui->lbl_phone->setText(p->getPhoneNumber());
    }
}
void Professortab::showProfInfo(QString id){

    p=Professor::professors.find(id);
    ui->lbl_fname->setText(p->getFirstName());
    ui->lbl_lname->setText(p->getSecondName());
    ui->lbl_age->setText(QString::number(p->getAge()));
    ui->lbl_title->setText(p->getTitle());
    ui->lbl_mail->setText(p->getEmail());
    ui->lbl_phone->setText(p->getPhoneNumber());
    buildCourseTable();

}
void Professortab::on_tableWidgets_prof_cellDoubleClicked(int row, int column)
{
    showProfInfo(ui->tableWidgets_prof->item(row,2)->text());
}


void Professortab::on_lineEdit_textChanged(const QString &arg1)
{
    if(!ui->lineEdit->text().isEmpty())
       { QStringList list ;
        foreach (QTableWidgetItem* item, ui->tableWidgets_prof->findItems(ui->lineEdit->text(),Qt::MatchContains)) {
            list <<item->text();
        }

        QCompleter *c=new QCompleter(list);
        c->setCaseSensitivity(Qt::CaseInsensitive);
    c->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
        ui->lineEdit->setCompleter(c);}
    else
        buildProfTable();
}


void Professortab::on_lineEdit_editingFinished()
{
    ui->tableWidgets_prof->clearContents();
    ui->tableWidgets_prof->setRowCount(0);
    QTableWidgetItem *item;
    QTableWidget *x = ui->tableWidgets_prof;

QMap<QString, Professor>::iterator j;
    QMap<QString, Professor>::iterator i = Professor::professors.begin();
    while(i!=Professor::professors.end()){
      if(ui->lineEdit->text()==i->get_full_name()||ui->lineEdit->text()==i->getTitle())
       { x->insertRow(x->rowCount());
        item = new QTableWidgetItem;
        item->setText(i.value().get_full_name());
        ui->tableWidgets_prof->setItem(ui->tableWidgets_prof->rowCount()-1,0,item);
        item = new QTableWidgetItem;
        item->setText(i.value().getTitle());
        ui->tableWidgets_prof->setItem(ui->tableWidgets_prof->rowCount()-1,1,item);
        item = new QTableWidgetItem;
        item->setText(i.key());
        ui->tableWidgets_prof->setItem(ui->tableWidgets_prof->rowCount()-1,2,item); }
      i++;
    }
}

void Professortab::on_show_clicked()
{
    if(ui->tableWidgets_prof->selectedItems().size()==1)
     on_tableWidgets_prof_cellDoubleClicked(ui->tableWidgets_prof->selectedItems()[0]->row(),ui->tableWidgets_prof->selectedItems()[0]->column());
    else
       QMessageBox::warning(nullptr,"Error","Please select one students");
}

void Professortab::add_to_course(int x)
{
    foreach (QTableWidgetItem* item, ui->tableWidgets_prof->selectedItems())
    {
        c[x]->addProfessor(ui->tableWidgets_prof->item(item->row(),2)->text());
        Professor::professors[ui->tableWidgets_prof->item(item->row(),2)->text()].addCourse(c[x]->getCode());
        if(ui->lbl_fname->text()+" "+ui->lbl_lname->text()==ui->tableWidgets_prof->item(item->row(),0)->text())
        buildCourseTable();
    }

}

void Professortab::on_delete_clicked()
{  QString deleted_id;
    if(ui->tbl_courses->selectedItems().size()!=0)
    {
        foreach (QTableWidgetItem* item, ui->tbl_courses->selectedItems())
        {deleted_id=ui->tbl_courses->item(item->row(),1)->text();
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
                ui->tableWidgets_prof->removeAction(actions[i]);
            Course::courses.remove(deleted_id);
        }
        buildCourseTable();
    }
    else if(ui->tableWidgets_prof->selectedItems().size()!=0)
    {
        ui->tbl_courses->clearContents();
        ui->tbl_courses->setRowCount(0);
        ui->lbl_age->clear();
        ui->lbl_fname->clear();
        ui->lbl_lname->clear();
        ui->lbl_title->clear();
        ui->lbl_mail->clear();
        ui->lbl_phone->clear();

        foreach (QTableWidgetItem* item, ui->tableWidgets_prof->selectedItems())
        {
            deleted_id=ui->tableWidgets_prof->item(item->row(),2)->text();
            QMap<QString,Professor>::Iterator j=Professor::professors.find(deleted_id);


            QSet<QString>::ConstIterator c = j->getCourses().cbegin();
            while(c!= j->getCourses().cend())
            {
                Course::courses.find(*c)->deleteProf(deleted_id);
                c++;
            }
            Professor::professors.remove(deleted_id);
        }
        rebuildProfTable();
    }
}

void Professortab::on_remove_clicked()
{
    QString deleted_id;
    foreach (QTableWidgetItem* item, ui->tbl_courses->selectedItems())
    {
        deleted_id=ui->tbl_courses->item(item->row(),1)->text();
       QMap<QString,Course>::Iterator j=Course::courses.find(deleted_id);
p->removeCourse(j->getCode());
j->deleteProf(p->getId());
buildCourseTable();
}
}


void Professortab::on_pushButton_editprof_clicked()
{
if(!ui->lbl_mail->text().isEmpty())
   {editprof[0] = new editProfessor(nullptr,p);
connect(editprof[0],SIGNAL(r()),this,SLOT(rebuildProfTable()));
  editprof[0]->show();
}
else
    QMessageBox::warning(nullptr,"Error","Choose professor");
}
