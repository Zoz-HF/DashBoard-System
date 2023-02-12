#include "coursestab.h"
#include "card.h"
#include "card.h"
#include "ui_coursestab.h"
#include "course.h"
#include <QCompleter>
#include <qvalidator.h>
CoursesTab::CoursesTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoursesTab)
{
    mapper =new QSignalMapper(this);
    m=new QSignalMapper(this);
    setAttribute(Qt::WA_DeleteOnClose);
    addCourse[0]=new addcourse2();
    connect(addCourse[0],SIGNAL(button(QString,QString)),this,SLOT(newcard(QString,QString)));
    ui->setupUi(this);
    courseBuild();
}

void CoursesTab::courseBuild(){
    int i=0;
    while(!ui->CardsLayout->isEmpty())
           { ui->CardsLayout->itemAt(i)->widget()->close();
    i++;}
    Card * card;
c.clear();
    QMap<QString,Course>::iterator s =Course::courses.begin();
    while(s != Course::courses.end())
    {
        c.push_back(s->getCode());
        c.push_back(s->getName());
    card = new Card(this,s->getName(),s.key());
    ui->CardsLayout->addWidget(card);
    s++;
    connect(card,SIGNAL(deleted()),mapper,SLOT(map()));
    mapper->setMapping(card,j);
    connect(card,SIGNAL(ref()),m,SLOT(map()));
    m->setMapping(card,1);
    j++;
    }
    connect(mapper,SIGNAL(mappedInt(int)),this,SLOT(remove(int)));
    connect(m,SIGNAL(mappedInt(int)),this,SLOT(r(int)));
}
CoursesTab::~CoursesTab()
{
    delete ui;
}

void CoursesTab::on_add_clicked()
{
    addCourse[0]->show();
    addCourse[0]->buildComboBox();
}

void CoursesTab::remove(int index)
{
    ui->CardsLayout->itemAt(index)->widget()->close();
}
void CoursesTab::newcard(QString name,QString code)
{
    Card * card = new Card(this,name,code);
        ui->CardsLayout->addWidget(card);
        connect(card,SIGNAL(deleted()),mapper,SLOT(map()));
        connect(card,SIGNAL(ref()),m,SLOT(map()));
        mapper->setMapping(card,j);
        m->setMapping(card,j);
        c.push_back(name);
        c.push_back(code);
        addCourse[0]=new addcourse2();
        connect(addCourse[0],SIGNAL(button(QString,QString)),this,SLOT(newcard(QString,QString)));
}

void CoursesTab::on_lineEdit_textChanged(const QString &arg1)
{
    if(!ui->lineEdit->text().isEmpty())
    {
        QCompleter *complite=new QCompleter(c);
        complite->setCaseSensitivity(Qt::CaseInsensitive);
        complite->setCompletionMode(QCompleter::PopupCompletion);
        ui->lineEdit->setCompleter(complite);

    }

    else
    {int i=0;
        while(!ui->CardsLayout->isEmpty())
       { ui->CardsLayout->itemAt(i)->widget()->close();

            i++;}
courseBuild();
    }

}


void CoursesTab::on_lineEdit_editingFinished()
{int i=0;
    while(!ui->CardsLayout->isEmpty())
           { ui->CardsLayout->itemAt(i)->widget()->close();
    i++;}
    Card * card;
    c.clear();
    QMap<QString,Course>::iterator s =Course::courses.begin();
    while(s != Course::courses.end())
    {if(s->getCode()==ui->lineEdit->text()||s->getName()==ui->lineEdit->text())
       { c.push_back(s->getCode());
        c.push_back(s->getName());
    card = new Card(this,s->getName(),s.key());
    ui->CardsLayout->addWidget(card);
    connect(card,SIGNAL(ref()),m,SLOT(map()));
    m->setMapping(card,j);
    connect(card,SIGNAL(deleted()),mapper,SLOT(map()));
    mapper->setMapping(card,j);
       j++;
        }s++;
    }
    connect(mapper,SIGNAL(mappedInt(int)),this,SLOT(remove(int)));

}

void CoursesTab::r(int c)
{
    int i=0;
        while(!ui->CardsLayout->isEmpty())
               { ui->CardsLayout->itemAt(i)->widget()->close();
        i++;}
        courseBuild();

}
