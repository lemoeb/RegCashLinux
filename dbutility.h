#ifndef DBUTILITY_H
#define DBUTILITY_H

#include <QtSql>
#include <QFileInfo>
#include <QSqlError>


class dbUtility
{
public:
    dbUtility();

    bool dbConnectMySql(QString,QString,QString,QString);
    bool dbConnectSqlite(void);

    QSqlQuery ricercaArticolo(QString);
    QSqlQuery recuperaSconti(void);
    bool salvaSconti(int,int,int,int,int);

    void chiudiScontrino(float);

private:
    QSqlDatabase db;// = QSqlDatabase::database();
    int dbType;
};

#endif // DBUTILITY_H
