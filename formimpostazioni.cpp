#include "formimpostazioni.h"
#include "ui_formimpostazioni.h"

formImpostazioni::formImpostazioni(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formImpostazioni)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint); //Set window with no title bar
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

}

void formImpostazioni::on_radio_sqlite_clicked()
{
    ui->grp_dbSetting->setEnabled(false);
}

void formImpostazioni::on_radio_mysql_clicked()
{
    ui->grp_dbSetting->setEnabled(true);
}
