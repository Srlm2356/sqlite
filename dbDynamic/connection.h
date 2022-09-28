#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include "db_library.h"

extern QSqlDatabase db;

static bool connection() //Подключение к бд
{
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dPath); //Её наименование. Если такой бд нет, она автоматически создается
    if (!db.open()) {
        qDebug() << "Cannot open database";
        return false;
    }
    return true;
}

#endif // CONNECTION_H
