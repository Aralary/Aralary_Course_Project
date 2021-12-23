#ifndef USERS_LIST_H
#define USERS_LIST_H

#include <QMainWindow>
#include "database.h"
#include <QSqlQueryModel>

namespace Ui {
class users_list;
}

class users_list : public QMainWindow {
    Q_OBJECT

public:
    explicit users_list(QWidget *parent = nullptr);

    ~users_list();

public slots:
    void refresh_list(const QString &login);

    void set_db(DataBase* DB);
private:
    DataBase* db;
    Ui::users_list *ui;
};

#endif // USERS_LIST_H
