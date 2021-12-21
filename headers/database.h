#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <sstream>
#include <string>
/* Директивы имен таблицы, полей таблицы и базы данных */
//#define DATABASE_HOSTNAME   "host1488"
//#define DATABASE_NAME       "users_data.db"

//"Users"         // Название таблицы
//"Login"         // Вторая колонка
//"Password"      // Третья колонка
//"Fname"         // Четвертая колонка
//"Sname"         // Пятая колонка
//"Birth"         // Шестая колонка
//"Email"         // Седьмая колонка
// Первая колонка содержит Autoincrement ID

class DataBase : public QObject {
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);

    ~DataBase();

    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();

    bool check_person(const QString &login, const QString &password);

    void change_password(const QString &login, const QString &password);

    void change_phone(const QString &login, const QString &phone);


    void change_favourite(const QString &login, const QString &game);

    bool person_exist(const QString &login);

    bool full_person_check(const QString &fname, const QString &sname, const QString &birth, const QString &login,
                           const QString &email);

    bool game_check(const QString &login, const QString &gname);


    void set_table(const QString &table);

    void add_money(const QString &login, const QString &add_cash, const QString &old_cash);

    void reduce_money(const QString &login, const QString &red_cash, const QString &old_cash);

    QString get_money(const QString& login);

    bool get_favourite(const QString &login, const QString &gname);

    QString phone(const QString &login);

    QString get_BirthDate(const QString& login);


    bool createTable(const QString& table);

private:
    /* Внутренние методы для работы с базой данных
     * */
    void closeDataBase();       // Закрытие базы данных
    bool openDataBase();        // Открытие базы данных
    bool restoreDataBase();     // Восстановление базы данных
    bool createTable();         // Создание базы таблицы в базе данных


public
    slots:
    bool inserIntoTable(const QVariantList &data);      // Добавление записей в таблицу



    bool inserIntoTable(const QString &login, const QString &password,
                        const QString &fname, const QString &sname, const QString &birth, const QString &email);
    bool inserIntoTable(const QString &login, const QString &gname);

    bool removeRecord(const int id); // Удаление записи из таблицы по её id

private:
    // Сам объект базы данных, с которым будет производиться работа
    QString DATABASE_HOSTNAME = "host1488";
    QString DATABASE_NAME = "users_data.db";
    QString TABLE = "Users";
    QSqlDatabase db;
};


#endif // DATABASE_H
