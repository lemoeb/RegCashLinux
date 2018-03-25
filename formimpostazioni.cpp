#include "formimpostazioni.h"
#include "ui_formimpostazioni.h"

formImpostazioni::formImpostazioni(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formImpostazioni)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::CustomizeWindowHint); //Set window with no title bar
    QString m_sSettingsFile = "./config/application.ini";
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);

    //recupero delle impostazioni
    //---------------------------
    int settingDbType=settings.value("dbType", "").toInt();

    QString settingDbAddress=settings.value("dbAddress", "").toString();
    QString settingDbName=settings.value("dbName", "").toString();
    QString settingDbPassword=settings.value("dbPassword", "").toString();
    QString settingDbUser=settings.value("dbUser", "").toString();

    //Section SyncShop
    //----------------
    settings.beginGroup("SyncShop");
    int settingShopOnline=settings.value("shopType", "").toInt();
    int settingSyncActive=settings.value("syncActive", "").toInt();
    settings.endGroup();

    //Section WebService Shop
    //-----------------------
    settings.beginGroup("wsShop");
    QString settingUrlShop=settings.value("urlShop", "").toString();
    QString settingWsShop=settings.value("wsShop", "").toString();
    QString settingApiKey=settings.value("apiKey", "").toString();
    settings.endGroup();

    //---------------------//
    // Valorizzazione Form //
    //---------------------//

    //Impostazioni DB
    switch(settingDbType){
        case 1:
            ui->radio_mysql->setChecked(true);
            ui->dbHost->setText(settingDbAddress);
            ui->dbName->setText(settingDbName);
            ui->dbuser->setText(settingDbUser);
            ui->dbPassword->setText(settingDbPassword);
            ui->grp_dbSetting->setEnabled(true);
        break;

        case 2:
            ui->radio_sqlite->setChecked(true);
            ui->grp_dbSetting->setEnabled(false);
        break;

        default:
        break;
    }

    //Impostazioni Shop Online
    //------------------------
    switch(settingShopOnline){
        case PRESTASHOP:
            ui->radio_shop_1->setChecked(true);
        break;

        case MAGENTO:
            ui->radio_shop_2->setChecked(true);
        break;

        case OS_COMMERCE:
            ui->radio_shop_3->setChecked(true);
        break;

    }

    //Impostazione Sincronizzazione Live
    //----------------------------------
    if (settingSyncActive==SYNC_ACTIVE){
        ui->ckLiveSync->setChecked(true);
    }else{
        ui->ckLiveSync->setChecked(false);
    }

    //Impostazione WebService
    //-----------------------
    if (settingUrlShop!="") {
        ui->shopAddress->setText(settingUrlShop);
    }
    if (settingWsShop!=""){
        ui->wsName->setText(settingWsShop);
    }
    if (settingApiKey!=""){
        ui->apiKey->setText(settingApiKey);
    }


}

formImpostazioni::~formImpostazioni()
{
    delete ui;
}

void formImpostazioni::on_btnAnnulla_clicked()
{
    this->close();
}

void formImpostazioni::on_btnConferma_clicked()
{
    QString m_sSettingsFile = "./config/application.ini";
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);

    settings.setValue("dbAddress", ui->dbHost->text());
    settings.setValue("dbName", ui->dbName->text());
    settings.setValue("dbPassword",ui->dbPassword->text());
    settings.setValue("dbUser",ui->dbuser->text());

    if (ui->radio_mysql->isChecked()){
      settings.setValue("dbType",DB_MYSQL);
    }else{
      settings.setValue("dbType",DB_SQLITE);
    }

    settings.beginGroup("SyncShop");
    if (ui->ckLiveSync->checkState()==SYNC_ACTIVE){
        settings.setValue("syncActive",SYNC_ACTIVE);
    }else{
        settings.setValue("syncActive",SYNC_DISACTIVE);
    }
    settings.endGroup();

    settings.beginGroup("wsShop");
        settings.setValue("urlShop",ui->shopAddress->text());
        settings.setValue("wsShop",ui->wsName->text());
        settings.setValue("apiKey",ui->apiKey->text());
    settings.endGroup();

    QMessageBox::information(this,INFO_TITLE,SETTING_SAVED,QMessageBox::Ok);
}

void formImpostazioni::on_radio_sqlite_clicked()
{
    ui->grp_dbSetting->setEnabled(false);
}

void formImpostazioni::on_radio_mysql_clicked()
{
    ui->grp_dbSetting->setEnabled(true);
}

