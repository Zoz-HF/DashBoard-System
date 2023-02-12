#ifndef EDITPROFESSOR_H
#define EDITPROFESSOR_H

#include <QWidget>
#include "professor.h"

namespace Ui {
class editProfessor;
}

class editProfessor : public QWidget
{
    Q_OBJECT
signals:
    void r();
public:
    explicit editProfessor(QWidget *parent = nullptr, QMap<QString, Professor>::iterator prof=Professor::professors.begin());
    ~editProfessor();

private slots:
    void on_pushButton_edit_clicked();

private:
    QMap<QString, Professor>::iterator p;
    Ui::editProfessor *ui;
};

#endif // EDITPROFESSOR_H
