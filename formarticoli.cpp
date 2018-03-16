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

void formArticoli::disabilitaCampiText(){
    this->ui->txtDescrizione->setEnabled(false);
    this->ui->txtPrezzo->setEnabled(false);
    this->ui->txtGiacenza->setEnabled(false);
    this->ui->btnSalva->setEnabled(false);
}


void formArticoli::resetForm(){
    this->ui->txtDescrizione->clear();
    this->ui->txtPrezzo->clear();
    this->ui->txtGiacenza->clear();
    disabilitaInsMod();
    tipoSalvataggio=NO_ACTION;
}

void formArticoli::abilitaInserimento(){
    this->ui->btnSalva->setEnabled(true);
    this->ui->txtDescrizione->setEnabled(true);
    this->ui->txtPrezzo->setEnabled(true);
    this->ui->txtGiacenza->setEnabled(true);
    this->ui->btnModifica->setEnabled(false);
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
                      tipoSalvataggio=INSERIMENTO_ARTICOLO;
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

/**
 * @brief formArticoli::on_btnModifica_clicked
 */
void formArticoli::on_btnModifica_clicked()
{
    abilitaInserimento();
    tipoSalvataggio=MODIFICA_ARTICOLO;
}

/**
 * @brief formArticoli::on_txtArticolo_textChanged
 * @param arg1
 */
void formArticoli::on_txtArticolo_textChanged(const QString &arg1)
{
    resetForm();
    disabilitaInsMod();
}

/**
 * @brief formArticoli::on_btnSalva_clicked
 */
void formArticoli::on_btnSalva_clicked()
{
    int result=NO_ERROR;
    QString idArticolo=this->ui->txtArticolo->text();
    QString descArticolo=this->ui->txtDescrizione->toPlainText();
    double prezzo=this->ui->txtPrezzo->text().toFloat();
    int giacenza=this->ui->txtGiacenza->text().toInt();
    result=db2.salvaArticolo(idArticolo,descArticolo,prezzo,giacenza,tipoSalvataggio);

    if (result==NO_ERROR){
        switch(tipoSalvataggio){
            case INSERIMENTO_ARTICOLO:
                QMessageBox::information(this,"Info","Nuovo articolo inserito",QMessageBox::Ok);
            break;
            case MODIFICA_ARTICOLO:
                QMessageBox::information(this,"Info","Articolo Modificato",QMessageBox::Ok);
            break;
        }
        resetForm();
    }else{
        switch(tipoSalvataggio){
            case INSERIMENTO_ARTICOLO:
                QMessageBox::critical(this,"Errore","Errore durante l'inserimento dell'articolo",QMessageBox::Ok);
            break;
            case MODIFICA_ARTICOLO:
                QMessageBox::critical(this,"Errore","Errore durante la modifica dell'articolo",QMessageBox::Ok);
            break;
        }

    }

}
