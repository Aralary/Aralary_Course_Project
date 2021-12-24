#ifndef INSERTER_H
#define INSERTER_H

#include "database.h"
#include <QString>

class inserter
{
public:
    inserter();
    inserter(const QString& Login, const QString& Password, const QString& Fname,const QString& Sname, const QString& Birth,const QString& Email);

    void insert_person();
private:
    DataBase* db;
    QString login;
    QString password;
    QString fname;
    QString sname;
    QString birth;
    QString email;
};

#endif // INSERTER_H
