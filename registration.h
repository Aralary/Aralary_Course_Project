#ifndef REGISTRATION_H

#include <QMainWindow>
#include "database.h"
#include<regex>
#include<stdio.h>
#include "checker.h"
#include <thread>

#define REGISTRATION_H


namespace Ui {
class registration;
}

class registration : public QMainWindow {
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);

    ~registration();

    void ru_lang();

    void en_lang();

public slots:
    void set_db(DataBase* DB);

signals:
    void firstWindow();
private:

    void clear_window();

    private
    slots:
    void on_pushButton_clicked();

    void on_checkBox_2_stateChanged(int);

    void on_checkBox1_stateChanged(int);


    void on_pushButton_3_clicked();

private:
    DataBase *db;
    Ui::registration *ui;
};

#endif // REGISTRATION_H
