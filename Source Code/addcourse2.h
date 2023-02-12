#ifndef ADDCOURSE2_H
#define ADDCOURSE2_H

#include <QDialog>

namespace Ui {
class addcourse2;
}

class addcourse2 : public QDialog
{
    Q_OBJECT

public:
    explicit addcourse2(QWidget *parent = nullptr);
    void buildComboBox();
    ~addcourse2();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_hall_currentIndexChanged(int index);

    void on_comboBox_days_currentIndexChanged(int index);

signals:
   void button(QString name,QString code);

private:

    Ui::addcourse2 *ui;
};

#endif // ADDCOURSE2_H
