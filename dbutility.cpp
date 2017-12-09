#include "dbutility.h"

const int DBMYSQL=1;
const int DBSQLITE=2;

dbUtility::dbUtility()
{

}

/**
 * @brief dbUtility::dbConnectMySql
 * @param dbName
 * @param dbAddress
 * @param dbUser
 * @param dbPassword
 * @return
 */
bool dbUtility::dbConnectMySql(QString dbName,QString dbAddress,QString dbUser,QString dbPassword){

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbAddress);
    db.setDatabaseName(dbName);
    db.setPort(3306);
    db.setUserName(dbUser);
    db.setPassword(dbPassword);

    if (!db.open()){
        return false;
    }
    dbType=DBMYSQL;
    return true;
}


/**
 * @brief dbConnectSqlite
 * @return
 */
bool dbUtility::dbConnectSqlite(void){

    QFileInfo check_file("./db/regcash.sqlite");

    if (check_file.exists() && check_file.isFile()) {

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./db/regcash.sqlite");

        if (!db.open()){
            return false;
        }

    } else {
        return false;
    }
    dbType=DBSQLITE;
    return true;
}

/**
 * @brief ricercaArticolo
 * @param codArticolo
 * @return
 */
QSqlQuery dbUtility::ricercaArticolo(QString codArticolo){

    QString sqlSelect;
    QSqlQuery query;
    sqlSelect="select a.codArticolo,a.descarticolo,a.prezzoArticolo, b.giacenza from tbarticoli a, tbgiacenze b  WHERE a.idArticolo=b.idArticolo AND a.codarticolo=:codArticolo";
    query.prepare(sqlSelect);
    query.bindValue(":codArticolo", codArticolo);

    query.exec();
    return query;
}


/**
 * @brief dbUtility::chiudiScontrino
 * @param totale
 */
void dbUtility::chiudiScontrino(float totale)
{

}
