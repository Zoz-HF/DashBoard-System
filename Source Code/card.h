#ifndef CARD_H
#define CARD_H

#include <QWidget>

namespace Ui {
class Card;
}

class Card : public QWidget
{
    Q_OBJECT

signals:
    void deleted();
     void ref();
public:
    explicit Card(QWidget *parent = nullptr,QString name="",QString code="");
    ~Card();

private:
    Ui::Card *ui;
QString code;
// QWidget interface
QVector<int> getTimeIndexes(QStringList a, QString hall);
protected:

    virtual void paintEvent(QPaintEvent *event) override;
private slots:
void signal();
    void on_pushButton_show_clicked();

    void on_delete_clicked();
};

#endif // CARD_H
