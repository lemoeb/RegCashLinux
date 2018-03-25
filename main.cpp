#include "regcashmain.h"
#include "formpagamento.h"
#include "dbutility.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QObject>
#include <QMessageBox>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool dbConnect;
    dbUtility dbConn;
    QMessageBox messageBox;
    int dbType=0;


    QString m_sSettingsFile = "./config/application.ini";
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);

    dbType=settings.value("dbType", "").toInt();


    if (dbType==1){
      QString dbName=settings.value("dbName", "").toString();
      QString dbAddress=settings.value("dbAddess", "").toString();
      QString dbUser=settings.value("dbUser", "").toString();
      QString dbPassword=settings.value("dbPassword", "").toString();
      dbConnect=dbConn.dbConnectMySql(dbName,dbAddress,dbUser,dbPassword);
    }
    else if (dbType==2){
       dbConnect=dbConn.dbConnectSqlite();
    }
    else
    {
        messageBox.setText("File di conigurazione non presente o danneggiato");
        messageBox.exec();
        exit(1);
    }


    if (dbConnect==true){
        qInfo("Connessione DB OK");
    }
    else
    {
        messageBox.setText("Impossibile connettersi al DB");
        messageBox.exec();
        exit(1);
    }


    RegCashMain w;

    w.show();

    return a.exec();
}

