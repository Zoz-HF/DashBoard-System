#ifndef COURSESTAB_H
#define COURSESTAB_H
#include "addcourse2.h"
#include <QWidget>
#include <QSignalMapper>
namespace Ui {
class CoursesTab;
}

class CoursesTab : public QWidget
{
    Q_OBJECT

public:
    explicit CoursesTab(QWidget *parent = nullptr);
    void courseBuild();
    ~CoursesTab();

private slots:
    void newcard(QString name,QString code);
    void on_add_clicked();
    void remove(int index);
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_editingFinished();

   void r(int c);
private:
    QStringList c;
    int j=0;
    QSignalMapper *mapper;
    QSignalMapper *m;
    Ui::CoursesTab *ui;
    QVector<addcourse2*> addCourse{1};
};

#endif
// COURSESTAB_H
