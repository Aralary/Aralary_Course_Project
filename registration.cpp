#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <sstream>

registration::registration(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::registration) {
    ui->setupUi(this);
}

registration::~registration() {
    delete ui;
}


void registration::clear_window()
{
    ui->fname_line->clear();
    ui->sname_line->clear();
    ui->birth_line->setDate(ui->birth_line->minimumDate());
    ui->email_line->clear();
    ui->pass_message->clear();
    ui->login_label->clear();
    ui->date_message->clear();
    ui->mail_label->clear();
    ui->log_line->clear();
    ui->pass1->clear();
    ui->pass2->clear();
}


void registration::on_checkBox_2_stateChanged(int) {
    if (ui->checkBox_2->isChecked()) {
        ui->pass2->setEchoMode(QLineEdit::Normal);
    } else {
        ui->pass2->setEchoMode(QLineEdit::Password);
    }
}


void registration::on_checkBox1_stateChanged(int) {
    if (ui->checkBox1->isChecked()) {
        ui->pass1->setEchoMode(QLineEdit::Normal);
    } else {
        ui->pass1->setEchoMode(QLineEdit::Password);
    }
}


void registration::on_pushButton_3_clicked() {
    ui->login_label->clear();
    ui->pass_message->clear();
    ui->date_message->clear();
    ui->mail_label->clear();


    QString fname = ui->fname_line->text();
    QString sname = ui->sname_line->text();
    QString birth = ui->birth_line->text();
    QString email = ui->email_line->text();
    QString login = ui->log_line->text();
    QString password = ui->pass1->text();


    if (!login.isEmpty() && !password.isEmpty() && !fname.isEmpty() && !sname.isEmpty() &&
        !email.isEmpty()) {
        DataBase db;
        db.connectToDataBase();
        if (db.person_exist(login)) {
            ui->login_label->setText("This Login is already taken");
            return;
        }
        if (password != ui->pass2->text()) {
            ui->pass_message->setText("Passwords are not the same");
            return;
        }
        if (!Email_check(email)) {
            ui->mail_label->setText("Incorrect email adress");
            return;
        }
        db.inserIntoTable(login, password, fname, sname, birth, email);
        QMessageBox::StandardButton button = QMessageBox::information(this, "Registration",
                                                                          "You have successfully registered",
                                                                          QMessageBox::Ok);
        if (button == QMessageBox::Ok) {
            close();
            clear_window();
            emit firstWindow();
         }
    } else {
       QMessageBox::information(this, "Attention", "Please fill in all empty lines");
    }
}

void registration::on_pushButton_clicked() {
    this->close();
    clear_window();
    emit firstWindow();
}

bool registration::Email_check(const QString &email) {
    std::string mail = email.toStdString();
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(mail, pattern);
}


