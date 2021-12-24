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
#include <QCryptographicHash>
#include <mutex>
<<<<<<< Updated upstream
=======
#include <thread>
#include <atomic>
#include <QThread>
#include <queue>
#include <future>
#include <condition_variable>
>>>>>>> Stashed changes

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

    QString get_money(const QString &login);

    bool get_favourite(const QString &login, const QString &gname);

    QString phone(const QString &login);

    QString get_BirthDate(const QString &login);

    bool createTable(const QString &table);

    void closeDataBase();
private:

<<<<<<< Updated upstream
       // Закрытие базы данных
=======
    void answer();

    void DbProcess();

>>>>>>> Stashed changes
    bool openDataBase();        // Открытие базы данных
    bool restoreDataBase();     // Восстановление базы данных
    bool createTable();         // Создание базы таблицы в базе данных

    public
    slots:
<<<<<<< Updated upstream
    bool inserIntoTable(
            const QVariantList &data
            );      // Добавление записей в таблицу



=======
    bool inserIntoTable(const QString& table, const QVariantList &data);      // Добавление записей в таблицу


>>>>>>> Stashed changes
    bool inserIntoTable(const QString &login, const QString &password,
                        const QString &fname, const QString &sname, const QString &birth, const QString &email);

    bool inserIntoTable(const QString &login, const QString &gname);

private:
<<<<<<< Updated upstream
=======
    explicit DataBase(QObject *parent = 0);
    DataBase(const DataBase& db) = delete;
    DataBase& operator=(const DataBase&) = delete;

    static std::queue<QSqlQuery> requests;
    static std::unique_lock<std::mutex> q_lock;
    static std::condition_variable cv;
>>>>>>> Stashed changes
    QString DATABASE_HOSTNAME = "host1488";
    QString DATABASE_NAME = "users_data.db";
    QString TABLE = "Users";
    QSqlDatabase db;
    std::mutex g_lock;
};


#endif // DATABASE_H
