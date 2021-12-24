#include "inserter.h"

inserter::inserter()
{

}

inserter::inserter(const QString &Login, const QString &Password, const QString &Fname, const QString &Sname, const QString &Birth, const QString &Email)
    : login(Login), password(Password), fname(Fname), sname(Sname), birth(Birth), email(Email)
{

}

void inserter::insert_person()
{
    db->inserIntoTable(login,password,fname,sname,birth,email);
}
