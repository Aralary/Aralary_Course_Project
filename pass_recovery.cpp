#include "pass_recovery.h"
#include "ui_pass_recovery.h"
#include <QMessageBox>

pass_recovery::pass_recovery(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::pass_recovery) {
    ui->setupUi(this);
}

pass_recovery::~pass_recovery() {
    delete ui;
}

void pass_recovery::on_pushButton_clicked() {
    this->close();
    clear_window();
    emit firstWindow();
}


void pass_recovery::on_pushButton_2_clicked() {
    ui->pass_message->clear();
    QString fname = ui->lineEdit->text();
    QString sname = ui->lineEdit_2->text();
    QString birth = ui->lineEdit_3->text();
    QString login = ui->lineEdit_4->text();
    QString email = ui->lineEdit_5->text();
    QString npas1 = ui->lineEdit_6->text();
    QString npas2 = ui->lineEdit_7->text();
    if (!fname.isEmpty() && !sname.isEmpty() && !birth.isEmpty() &&
        !login.isEmpty() && !email.isEmpty() && !npas1.isEmpty() && !npas2.isEmpty()) {
        if (npas1 == npas2) {
            DataBase db;
            db.connectToDataBase();
            if (db.check_person(login, npas1)) {
                    ui->pass_message->setText("The new password must be different from the old one");
                return;
            }
            if (db.full_person_check(fname, sname, birth, login, email)) {
                db.change_password(login, npas1);
                QMessageBox::StandardButton button = QMessageBox::information(this, "Password recovery",
                                                                                  "You have successfully change your password",
                                                                                  QMessageBox::Ok);
                 if (button == QMessageBox::Ok) {
                     close();
                     clear_window();
                     emit firstWindow();
                 }
            } else {
                QMessageBox::information(this, "Attention", "Incorrect Data");
            }
        } else {
            ui->pass_message->setText("Passwords are not the same");
            return;
        }
    } else {
       QMessageBox::information(this, "Attention", "Please fill in all empty lines");
    }
}


void pass_recovery::on_checkBox_stateChanged(int)
{
    if (ui->checkBox->isChecked()) {
        ui->lineEdit_6->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    }
}


void pass_recovery::on_checkBox_2_stateChanged(int)
{
    if (ui->checkBox_2->isChecked()) {
        ui->lineEdit_7->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_7->setEchoMode(QLineEdit::Password);
    }
}

void pass_recovery::clear_window()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->setDate(ui->lineEdit_3->minimumDate());
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->pass_message->clear();
}

