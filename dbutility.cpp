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
 * @param tipoPagamento
 * @param dbTable
 * @param errore
 * @param numScontrino
 * @return
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

/**
 * @brief dbUtility::salvaArticolo
 * @param codArticolo
 * @param descArticolo
 * @param prezzo
 * @param giacenza
 * @param tipoSalvataggio
 * @return
 */
int dbUtility::salvaArticolo(QString codArticolo,QString descArticolo,float prezzo, int giacenza,int tipoSalvataggio){
    QString sqlQuery="";
    QSqlQuery query;
    int idArticolo=0;

    sqlQuery="SET autocommit = 0";
    query.prepare(sqlQuery);
    query.exec();

    switch(tipoSalvataggio){
        case INSERIMENTO_ARTICOLO:
            qDebug() << "Inserimento Articolo";
            sqlQuery="INSERT INTO tbarticoli (codArticolo,descArticolo,prezzoArticolo) values (:codArticolo,:descArticolo,:prezzoArticolo)";
            query.prepare(sqlQuery);
            query.bindValue(":codArticolo",codArticolo);
            query.bindValue(":descArticolo",descArticolo);
            query.bindValue(":prezzoArticolo",prezzo);
            query.exec();


            if (query.lastError().isValid()){
               // *errore=QString::fromStdString(query.lastError().text().toStdString());
               return ERR_INSERIMENTO_ARTICOLO;
            }
            else{
                    idArticolo=query.lastInsertId().toInt();
                    sqlQuery="INSERT INTO tbgiacenze (idArticolo,giacenza) values (:idArticolo,:giacenza)";
                    query.prepare(sqlQuery);
                    query.bindValue(":idArticolo",idArticolo);
                    query.bindValue(":giacenza",giacenza);
                    query.exec();
                    if (query.lastError().isValid()){
                      return ERR_INSERIMENTO_ARTICOLO;
                    }
            }
        break;
        case MODIFICA_ARTICOLO:

            //recupero idArticolo
            //-------------------
            sqlQuery="SELECT idArticolo FROM tbarticoli WHERE codArticolo=:codArticolo ";
            query.prepare(sqlQuery);
            query.bindValue(":codArticolo", codArticolo);
            query.exec();
            query.next();
            idArticolo=query.value(0).toInt();

            if (idArticolo!=0){
                sqlQuery="UPDATE tbarticoli set descArticolo=:descArticolo,prezzoArticolo=:prezzo WHERE idArticolo=:idArticolo";
                query.prepare(sqlQuery);
                query.bindValue(":idArticolo", idArticolo);
                query.bindValue(":descArticolo", descArticolo);
                query.bindValue(":prezzo", prezzo);
                query.exec();
                if (query.lastError().isValid()){
                    return ERR_MODIFICA_ARTICOLO;
                }
                else{
                    sqlQuery="UPDATE tbgiacenze set giacenza=:giacenza WHERE idArticolo=:idArticolo";
                    query.prepare(sqlQuery);
                    query.bindValue(":idArticolo", idArticolo);
                    query.bindValue(":giacenza", giacenza);
                    query.exec();
                    if (query.lastError().isValid()){
                        return ERR_MODIFICA_ARTICOLO;
                    }

                }

            }
            else{
                return ERR_MODIFICA_ARTICOLO;
            }
        break;
    }
    sqlQuery="commit";
    query.prepare(sqlQuery);
    query.exec();
    return NO_ERROR;
}

/**
 * @brief report
 * @param tipoReport
 * @param dataDa
 * @param dataA
 * @param limiteRighe
 * @param limiteArticolo
 * @return
 */
QSqlQuery dbUtility::report(QString *descErrore,int *numErrore,int tipoReport,QString dataDa,QString dataA,int limiteRighe,QString limiteArticolo, int filtraData,int filtraRighe,int filtraArticolo){

    QString sqlSelect;
    QSqlQuery query;

    switch(tipoReport){
        case REPORT_LISTA_ARTICOLI:
            sqlSelect="SELECT a.codArticolo,a.descArticolo,a.prezzoArticolo,b.giacenza "
                    "FROM tbarticoli a, tbgiacenze b where a.idArticolo=b.idArticolo "
                    "order by a.codArticolo";
            query.prepare(sqlSelect);
            query.exec();
        break;

        case REPORT_ARTICOLI_NO_GIACENZA:
            sqlSelect="SELECT a.codArticolo,a.descArticolo,a.prezzoArticolo,b.giacenza "
                    "FROM tbarticoli a, tbgiacenze b where a.idArticolo=b.idArticolo AND b.giacenza<=0 "
                    "order by a.codArticolo";
            query.prepare(sqlSelect);
            query.exec();
        break;

        case REPORT_ARTICOLI_VENDUTI:
            sqlSelect="SELECT count(a.codArticolo) as totale,a.codArticolo,a.descArticolo "
                   "FROM tbarticoli a, tbuscite b "
                   "where a.idArticolo=b.idArticolo ";
            if (filtraData==2){
                sqlSelect += "AND b.dataUscita >=:dataDa AND and b.dataUscita <=:dataA ";
            }
            if (filtraArticolo==2){
                sqlSelect += "AND a.codArticolo=:cordArticolo ";
            }
            sqlSelect += "group by a.codArticolo,a.descArticolo "
                    "order by a.codArticolo ";
            if (filtraRighe==2){
                sqlSelect += "limit 0,:righe";
            }

            query.prepare(sqlSelect);

            if (filtraData==2){
                query.bindValue("dataDa",dataDa);
                query.bindValue("dataDa",dataA);
            }

            if (filtraArticolo==2) { query.bindValue("codArticolo",limiteArticolo); }
            if (filtraRighe == 2) { query.bindValue(":righe",limiteRighe); }
            query.exec();

        break;

        case REPORT_ARTICOLI_PIU_VENDUTI:
            sqlSelect="SELECT count(a.codArticolo) as totale,a.codArticolo,a.descArticolo "
                   "FROM tbarticoli a, tbuscite b "
                   "where a.idArticolo=b.idArticolo ";
            if (filtraData==2){
                sqlSelect += "AND b.dataUscita >=:dataDa AND and b.dataUscita <=:dataA ";
            }
            if (filtraArticolo==2){
                sqlSelect += "AND a.codArticolo=:cordArticolo ";
            }
            sqlSelect += "group by a.codArticolo,a.descArticolo "
                    "order by totale desc ";


            if (filtraRighe==2){
                sqlSelect += "limit 0,:righe";
            }
            else{
                sqlSelect += "limit 0,10";
            }

            query.prepare(sqlSelect);

            if (filtraData==2){
                query.bindValue("dataDa",dataDa);
                query.bindValue("dataDa",dataA);
            }

            if (filtraArticolo==2) { query.bindValue("codArticolo",limiteArticolo); }
            if (filtraRighe == 2) { query.bindValue(":righe",limiteRighe); }
            query.exec();

        break;

        case REPORT_ARTICOLI_PIU_PROFITTO:{
            sqlSelect="SELECT sum(b.prezzoScontato) as totale,a.codArticolo,a.descArticolo "
                   "FROM tbarticoli a, tbuscite b "
                   "where a.idArticolo=b.idArticolo ";
            if (filtraData==2){
                sqlSelect += "AND b.dataUscita >=:dataDa AND and b.dataUscita <=:dataA ";
            }
            if (filtraArticolo==2){
                sqlSelect += "AND a.codArticolo=:cordArticolo ";
            }
            sqlSelect += "group by a.codArticolo,a.descArticolo "
                    "order by totale desc ";


            if (filtraRighe==2){
                sqlSelect += "limit 0,:righe";
            }
            else{
                sqlSelect += "limit 0,10";
            }
            qDebug() << sqlSelect;
            query.prepare(sqlSelect);

            if (filtraData==2){
                query.bindValue("dataDa",dataDa);
                query.bindValue("dataDa",dataA);
            }

            if (filtraArticolo==2) { query.bindValue("codArticolo",limiteArticolo); }
            if (filtraRighe == 2) { query.bindValue(":righe",limiteRighe); }
            query.exec();
        }
        break;
    }



    return query;
}
