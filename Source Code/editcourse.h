#ifndef EDITCOURSE_H
#define EDITCOURSE_H

#include "course.h"
#include <QWidget>

namespace Ui {
class editCourse;
}

class editCourse : public QWidget
{
    Q_OBJECT

public:
    explicit editCourse(QWidget *parent = nullptr, QMap<QString,Course>::Iterator c=Course::courses.begin());
    ~editCourse();
    void buildComboBox();

private slots:

    void on_pushButton_clicked();

    void on_comboBox_hall_currentIndexChanged(int index);

    void on_comboBox_days_currentIndexChanged(int index);

signals:
    void refresh_display_course();
private:

    QString currentName,currentcode,currentTime,currentHall;
    QStringList splitedTime;
    Ui::editCourse *ui;
    QMap<QString,Course> ::iterator course;
    bool checks();
    QVector<int> getTimeIndexes(QStringList a, QString hall);
};

#endif // EDITCOURSE_H
