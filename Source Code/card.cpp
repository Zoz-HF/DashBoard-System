#include "card.h"
#include "ui_card.h"
#include "displaycourse.h"
#include <QPainter>

Card::Card(QWidget *parent,QString name,QString code) :
    QWidget(parent),
    ui(new Ui::Card)
{setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    ui->label_name->setText(name);
    ui->label_code->setText(code);
    this->code=code;
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *show=new QAction("Show information", this);
    connect(show,SIGNAL(triggered()),this,SLOT(on_pushButton_show_clicked()));
    show->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    addAction(show);
    QAction *dele=new QAction("Delete course", this);
    connect(dele,SIGNAL(triggered()),this,SLOT(on_delete_clicked()));
    dele->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    addAction(dele);
}

Card::~Card()
{
    delete ui;
}

// just to draw a border. could also use stylesheet
void Card::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawRect(0,0,width()-1, height()-1);

}

void Card::signal()
{
    emit ref();
}


void Card::on_pushButton_show_clicked()
{
    displayCourse *display = new displayCourse(nullptr,code);
    display->show();
    connect(display,SIGNAL(refresh()),this,SLOT(signal()));
}

void Card::on_delete_clicked()
{
      QMap<QString,Course>::Iterator j=Course::courses.find(code);


QMap<QString,float>::ConstIterator c = j->getStudents().cbegin();
while(c!= j->getStudents().cend())
{
Student::students.find(c.key())->removeCourseFromStudent(code);
    c++;
}
QSet<QString>::ConstIterator p = j->professors.cbegin();
while(p != j->professors.cend())
{
Professor::professors.find(*p)->removeCourse(code);
    p++;
}

QVector<int> v=getTimeIndexes(Course::courses[code].getTime().split(" "),Course::courses[code].getLectureHall());
Course::setDayHallTime(v[0],v[1],v[2],false);
Course::courses.remove(code);
emit deleted();

}

QVector<int> Card::getTimeIndexes(QStringList a,QString hall){

    QVector<int> v(3);
    if(a[0]=="Sunday") v[0]=0;
    else if(a[0]=="Monday") v[0]=1;
    else if(a[0]=="Tuesday") v[0]=2;
    else if(a[0]=="Wednesday") v[0]=3;
    else  v[0]=4;

    if(hall=="3201") v[1]=0;
    else if(hall=="1125") v[1]=1;
    else if(hall=="3101") v[1]=2;
    else if(hall=="3102") v[1]=3;
    else  v[1]=4;

    if(a[1]=="08:30-10:00") v[2]=0;
    else if(a[1]=="10:15-11:45") v[2]=1;
    else if(a[1]=="12:15-01:45") v[2]=2;
    else if(a[1]=="02:00-03:30") v[2]=3;
    else  v[2]=4;

    return v;
}
