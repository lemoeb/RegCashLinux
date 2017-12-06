#include "regcashmain.h"
#include "formpagamento.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("dbCassa");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root");
    if( !db.open() )
    {
        //qDebug(db.lastError());
        qFatal( "Failed to connect." );
    }
    else{
        qInfo("Connessione DB OK");
    }

    //RegCashMain FormPrincipale;
    RegCashMain w;
    //formpagamento FrmPagamento;

    //QObject::connect (&FrmPagamento,SIGNAL(resetTable()),&w,SLOT(resetCashTable()));


    w.show();



    return a.exec();
}

