#ifndef DBUTILITY_H
#define DBUTILITY_H

#include <QtSql>
#include <QFileInfo>
#include <QSqlError>
#include <QDebug>
#include "customtable.h"
#include "azioni.h"
#include "errori.h"

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
    int salvaArticolo (QString,QString ,float, int,int);
    QSqlQuery report(QString *,int *,int,QString,QString,int,QString,int,int,int);

private:
    QSqlDatabase db;// = QSqlDatabase::database();
    int dbType;
};

#endif // DBUTILITY_H
