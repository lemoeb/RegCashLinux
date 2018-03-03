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
 * @brief dbUtility::recuperaScontoSpecifico
 * @param idSconto
 * @return int
 */
int dbUtility::recuperaScontoSpecifico(int idSconto){

    QString sqlSelect;
    QSqlQuery query;
    sqlSelect="select sconto from tbSconti WHERE idSconto=:idSconto";
    query.prepare(sqlSelect);
    query.bindValue(":idSconto", idSconto);
    query.exec();

    if (query.lastError().isValid()){
        return -1;
    }

    if (query.next()){
        return query.value(0).toInt();
    }
    else
    {
        return -102;
    }

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
int dbUtility::chiudiScontrino(float totale,int tipoPagamento, customTable *dbTable, QString *errore, QString *numScontrino )
{
    QSqlQuery query;
    QString sqlUpdate;
    QString sqlInsert;
    QString sqlSelect;
    QString esito="";
    QString codArticolo="";
    QDateTime now = QDateTime::currentDateTime();
    int righeTabella=dbTable->rowCount();
    int i=0;

    int scontrino=0;
    int idArticolo=0;
    double prezzo=0;
    int sconto=0;
    double pScontato=0;

    db.transaction();
    //Recupero Scontrino
    sqlSelect = "SELECT seq('scontrino')";
    query.prepare(sqlSelect);
    query.exec();
    query.next();

    if (query.lastError().isValid()){
         *errore=QString::fromStdString(query.lastError().text().toStdString());
        return -1;
    }
    else{
        scontrino=query.value(0).toInt();

        for (i=0;i<righeTabella;i++){

            codArticolo=dbTable->item(i,0)->text();
            prezzo=dbTable->item(i,3)->text().toFloat();
            sconto=dbTable->item(i,2)->text().replace('%',' ').toInt();
            pScontato=dbTable->item(i,4)->text().toFloat();
            sqlSelect="SELECT idArticolo from tbarticoli WHERE codArticolo=:codArticolo";
            query.prepare(sqlSelect);
            query.bindValue(":codArticolo", codArticolo);
            query.exec();
            query.next();
            idArticolo=query.value(0).toInt();
            //qDebug()<<"Articolo : " << codArticolo << " - idArticolo : " << QString::number(idArticolo);
            query.clear();

            sqlInsert="INSERT INTO tbuscite (idScontrino,idArticolo,prezzoUnitario,scontoApplicato,prezzoScontato,dataUscita,tipoPagamento) "
                      "values (:idScontrino,:idArticolo,:prezzoUnitario,:scontoApplicato,:prezzoScontato,:dataUscita,:tipoPagamento)";

            query.prepare(sqlInsert);
            query.bindValue(":idScontrino", QString::number(scontrino));
            query.bindValue(":idArticolo",QString::number(idArticolo));
            query.bindValue(":prezzoUnitario",prezzo);
            query.bindValue(":scontoApplicato",sconto);
            query.bindValue(":prezzoScontato",pScontato);
            query.bindValue(":dataUscita",now.toString("yyyy-MM-dd"));
            query.bindValue(":tipoPagamento",tipoPagamento);
            query.exec();

            if (query.lastError().isValid()){
                *errore=QString::fromStdString(query.lastError().text().toStdString());
               return -1;
            }


        }
        *numScontrino=QString::number(scontrino);
        return 0;
   }

}
