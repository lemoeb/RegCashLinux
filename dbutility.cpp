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
 * @brief recuperaSconti
 * @return
 */
QSqlQuery dbUtility::recuperaSconti(){

    QString sqlSelect;
    QSqlQuery query;
    sqlSelect="select * from tbSconti ORDER by idSconto";
    query.prepare(sqlSelect);

    query.exec();
    return query;
}

/**
 * @brief salvaSconti
 * @param sconto1
 * @param sconto2
 * @param sconto3
 * @param sconto4
 * @param sconto5
 * @return
 */
bool dbUtility::salvaSconti(int sconto1,int sconto2,int sconto3,int sconto4,int sconto5){
    QSqlQuery query;
    QString sqlUpdate;

    sqlUpdate="update tbSconti set sconto=:sconto WHERE idSconto=1";
    query.prepare(sqlUpdate);
    query.bindValue(":sconto", sconto1);
    query.exec();

    if (query.lastError().isValid()){
        return false;
    }

    sqlUpdate="update tbSconti set sconto=:sconto WHERE idSconto=2";
    query.prepare(sqlUpdate);
    query.bindValue(":sconto", sconto2);
    query.exec();

    if (query.lastError().isValid()){
        return false;
    }


    sqlUpdate="update tbSconti set sconto=:sconto WHERE idSconto=3";
    query.prepare(sqlUpdate);
    query.bindValue(":sconto", sconto3);
    query.exec();

    if (query.lastError().isValid()){
        return false;
    }

    sqlUpdate="update tbSconti set sconto=:sconto WHERE idSconto=4";
    query.prepare(sqlUpdate);
    query.bindValue(":sconto", sconto4);
    query.exec();

    if (query.lastError().isValid()){
        return false;
    }

    sqlUpdate="update tbSconti set sconto=:sconto WHERE idSconto=5";
    query.prepare(sqlUpdate);
    query.bindValue(":sconto", sconto5);
    query.exec();

    if (query.lastError().isValid()){
        return false;
    }

    return true;
}


/**
 * @brief dbUtility::chiudiScontrino
 * @param totale
 */
void dbUtility::chiudiScontrino(float totale)
{

}
