#include "money.h"
#include "ui_money.h"
#include <iostream>
#include <QDebug>
money::money(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::money)
{
    ui->setupUi(this);
//    ui->pushButton_2->setStyleSheet("QPushButton {text-align: left;}");
}

money::~money()
{
    delete ui;
}

void money::clear()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void money::set_person(const QString &log, const QString& money)
{
    login = log;
    old_money = money;
}

void money::on_pushButton_clicked()
{
    DataBase db1;
    QString number = ui->lineEdit->text();
    QString add_cash = ui->lineEdit_2->text();
    db1.connectToDataBase();
    QString db_number = db1.phone(login);

    if(!money_check(add_cash) || !phone_check(number)){
        QMessageBox::StandardButton reply = QMessageBox::information(this,"Error", "You entered an incorrect number or amount of money",QMessageBox::StandardButton::Ok);
        if(reply == QMessageBox::Ok){
            return;
        }
    }
    if(number.isEmpty()){
        if(!db_number.isEmpty()){
            QMessageBox::StandardButton reply = QMessageBox::question(this,"Attention", "Do you want to debit money from the linked number?",QMessageBox::Yes | QMessageBox::No);
            if(reply == QMessageBox::Yes){
                db1.add_money(login,add_cash,old_money);
                close();
                clear();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            }
        }else{
            QMessageBox::StandardButton reply = QMessageBox::warning(this,"Attention", "You don't have a linked number",QMessageBox::StandardButton::Ok);
            if(reply == QMessageBox::Ok){
                return;
            }
        }

    }else{
        if(db_number != number){
            QMessageBox::StandardButton reply = QMessageBox::question(this,"Attention", "Do you want to link this phone number to your account?",QMessageBox::Yes | QMessageBox::No);
            if(reply == QMessageBox::Yes){
                db1.change_phone(login,number);
                db1.add_money(login,add_cash,old_money);
                close();
                clear();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            }else{
                db1.add_money(login,add_cash,old_money);
                close();
                clear();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            }
        }else{
            QMessageBox::StandardButton reply = QMessageBox::information(this,"Replenishment", "You used a linked number. \n"
                                                                                            "You don't have to enter a phone number to top up your balance",QMessageBox::StandardButton::Ok);
            if(reply == QMessageBox::Ok){
                db1.add_money(login,add_cash,old_money);
                clear();
                close();
                emit send_status();
                emit refresh(login);
                emit firstWindow();
            }

        }
    }

}

bool money::money_check(const QString &str)
{
    std::string temp = str.toStdString();
    if(temp.empty()){
        return false;
    }
    if(std::count(temp.begin(),temp.end(),'.') > 1){
        return false;
    }
    for(const auto& it: temp){
        if(it<'0' || it>'9' ){
            if(it=='.'){
                continue;
            }
            return false;
        }
    }
    return true;
}

bool money::phone_check(const QString &str)
{
    std::string temp = str.toStdString();
    if(temp.empty()){
        return true;
    }
    if(temp.size() < 9 || temp.size() > 15 || temp[0] != '+'){
        return false;
    }
    for(size_t i = 1; i < temp.size(); ++i){
        if(temp[i]<'0' || temp[i]>'9'){
            return false;
        }
    }
    return true;
}


void money::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"Info","When you top up your balance, you will have the opportunity to link your phone number to your account.\nIf you already have a linked number, then you do not need to fill in the line with the number field. \nIf you want to change the linked number , then fill in the line for the phone number.");
}

