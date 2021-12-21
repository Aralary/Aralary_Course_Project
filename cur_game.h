#ifndef CUR_GAME_H
#define CUR_GAME_H
#include <QMessageBox>
#include <QDialog>
#include "database.h"
namespace Ui {
class cur_game;
}

class cur_game : public QDialog
{
    Q_OBJECT

public:
    explicit cur_game(QWidget *parent = nullptr);
    ~cur_game();


public slots:
    void set_game(const QString& login, const QString& gname);

signals:
    void refresh_money(const QString& login);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int);
private:
    bool check_age_for_game(const QString& date, const QString& min_age);
private:
    Ui::cur_game *ui;
    QString LOGIN;
};

#endif // CUR_GAME_H
