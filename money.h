#ifndef MONEY_H
#define MONEY_H

#include "database.h"
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class money;
}

class money : public QMainWindow
{
    Q_OBJECT

public:
    explicit money(QWidget *parent = nullptr);
    ~money();

    void clear();
signals:
    void firstWindow();

    void send_status();

    void refresh(const QString& log);

    public slots:
    void set_person(const QString& log,const QString& money);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    bool money_check(const QString& str);
    bool phone_check(const QString& str);

private:
    QString old_money;
    QString login;
    Ui::money *ui;
};

#endif // MONEY_H