#ifndef DBUTILITY_H
#define DBUTILITY_H

#include <QtSql>
#include <QFileInfo>
#include <QSqlError>
#include <QDebug>
#include "customtable.h"

class dbUtility
{
public:
    dbUtility();

    bool dbConnectMySql(QString,QString,QString,QString);
    bool dbConnectSqlite(void);

    QSqlQuery ricercaArticolo(QString);
    QSqlQuery recuperaSconti(void);
    int recuperaScontoSpecifico(int);
    bool salvaSconti(int,int,int,int,int);

    int chiudiScontrino(float,int,customTable *,QString *,QString *);

private:
    QSqlDatabase db;// = QSqlDatabase::database();
    int dbType;
};

#endif // DBUTILITY_H
