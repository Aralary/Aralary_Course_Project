#include "money.h"
#include "ui_money.h"
#include <iostream>
#include <QDebug>

money::money(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::money) {
    ui->setupUi(this);
}

money::~money() {
    delete ui;
}

void money::clear() {
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

//получаем данные из предыдущего окна о пользователе
void money::set_person(const QString &log, const QString &money) {
    login = log;
    old_money = money;
}

void money::set_db(DataBase *DB)
{
    db = DB;
}

//кнопка пополнить с проверками
void money::on_pushButton_clicked() {
    checker ch;
    QString number = ui->lineEdit->text();
    QString add_cash = ui->lineEdit_2->text();
    QString db_number = db->phone(login);

    if (!ch.money_check(add_cash) || !ch.phone_check(number)) {
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Error",
                                                                     "You entered an incorrect number or amount of money",
                                                                     QMessageBox::StandardButton::Ok);
        if (reply == QMessageBox::Ok) {
            return;
        }
    }
    if (number.isEmpty()) {
        if (!db_number.isEmpty()) {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Attention",
                                                                      "Do you want to debit money from the linked number?",
                                                                      QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                db->add_money(login, add_cash, old_money);
                close();
                clear();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            }
        } else {
            QMessageBox::StandardButton reply = QMessageBox::warning(this, "Attention",
                                                                     "You don't have a linked number",
                                                                     QMessageBox::StandardButton::Ok);
            if (reply == QMessageBox::Ok) {
                return;
            }
        }

    } else {
        number = QString(QCryptographicHash::hash(number.toUtf8(), QCryptographicHash::Sha256).toHex());
        if (db_number != number) {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Attention",
                                                                      "Do you want to link this phone number to your account?",
                                                                      QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {

                db->change_phone(login, number);
                db->add_money(login, add_cash, old_money);
                close();
                clear();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            } else {
                db->add_money(login, add_cash, old_money);
                close();
                clear();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            }
        } else {
            QMessageBox::StandardButton reply = QMessageBox::information(this, "Replenishment",
                                                                         "You used a linked number. \n"
                                                                         "You don't need to enter a phone number to top up your balance",
                                                                         QMessageBox::StandardButton::Ok);
            if (reply == QMessageBox::Ok) {
                db->add_money(login, add_cash, old_money);
                clear();
                close();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            }

        }
    }

}

//кнопка "?" с полезной информацией
void money::on_pushButton_2_clicked() {
    QMessageBox::information(this, "Info",
                             "When you top up your balance, you will have the opportunity to link your phone number to your account.\nIf you already have a linked number, then you do not need to fill in the line with the number field. \nIf you want to change the linked number , then fill in the line for the phone number.");
}

