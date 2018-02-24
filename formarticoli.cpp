#include "formarticoli.h"
#include "ui_formarticoli.h"

formArticoli::formArticoli(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formArticoli)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint); //Set window with no title bar
}

formArticoli::~formArticoli()
{
    delete ui;
}

void formArticoli::on_btnAnnulla_clicked()
{
    this->close();
}

void formArticoli::abilitaInserimento(){
    this->ui->btnSalva->setEnabled(true);
    this->ui->txtDescrizione->setEnabled(true);
    this->ui->txtPrezzo->setEnabled(true);
    this->ui->txtGiacenza->setEnabled(true);
}

void formArticoli::disabilitaInsMod(){
    this->ui->btnSalva->setEnabled(false);
    this->ui->btnModifica->setEnabled(false);
    this->ui->txtDescrizione->setEnabled(false);
    this->ui->txtPrezzo->setEnabled(false);
    this->ui->txtGiacenza->setEnabled(false);
}

void formArticoli::abilitaModifica(){
    this->ui->btnModifica->setEnabled(true);
}

void formArticoli::on_txtArticolo_returnPressed()
{

    QString par2Str = this->ui->txtArticolo->text();
    QMessageBox::StandardButton reply;
    //this->ui->txtArticolo->setText("");
    this->ui->txtDescrizione->setPlainText("");

    if (par2Str!=""){
        QString sqlSelect;
        sqlSelect="select a.descArticolo,a.prezzoArticolo,b.giacenza from tbarticoli a,tbgiacenze b where codArticolo='" + par2Str +"' AND a.idArticolo=b.idArticolo";
        QSqlQuery qry;

         if(qry.exec(sqlSelect)) {
             qry.next();
             int a=qry.numRowsAffected();
             if (a==0){
                 reply=QMessageBox::question(this,"Attenzione","Articolo non trovato effettuare l'inserimento?",QMessageBox::Yes|QMessageBox::No);

                  if (reply == QMessageBox::Yes) {
                      abilitaInserimento();
                  }


             }
             else
             {
                 this->ui->txtDescrizione->setPlainText(qry.value(0).toString());
                 this->ui->txtPrezzo->setText(qry.value(1).toString());
                 this->ui->txtGiacenza->setText(qry.value(2).toString());
                 abilitaModifica();
             }


         }
    }
}

void formArticoli::on_btnModifica_clicked()
{
    abilitaInserimento();
}
