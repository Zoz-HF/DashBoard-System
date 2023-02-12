#ifndef ADDPROFESSOR_H
#define ADDPROFESSOR_H

#include <QDialog>

namespace Ui {
class addprofessor;
}

class addprofessor : public QDialog
{
    Q_OBJECT
signals:
    void rebuildTable();

public:
    explicit addprofessor(QWidget *parent = nullptr);
    ~addprofessor();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_age_inputRejected();

private:
    Ui::addprofessor *ui;
};

#endif // ADDPROFESSOR_H
