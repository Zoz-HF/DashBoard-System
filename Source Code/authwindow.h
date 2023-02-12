#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H
#include <QWidget>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

private slots:
    void on_pushButton_SignUp_clicked();

    void on_pushButton_Login_clicked();

private:
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
