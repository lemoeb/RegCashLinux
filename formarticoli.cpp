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

void formArticoli::on_txtArticolo_returnPressed()
{

    QString par2Str = this->ui->txtArticolo->text();
    //this->ui->txtArticolo->setText("");
    this->ui->txtDescrizione->setPlainText("");

    if (par2Str!=""){
        QString sqlSelect;
        sqlSelect="select descArticolo from tbarticoli where codArticolo='" + par2Str +"'";
        QSqlQuery qry;

         if(qry.exec(sqlSelect)) {
             qry.next();
             int a=qry.numRowsAffected();
             if (a==0){
                 QMessageBox::critical(this,"Errore","Articolo non trovato",QMessageBox::Ok);
             }
             else
             {
                 this->ui->txtDescrizione->setPlainText(qry.value(0).toString());
             }


         }
    }
}
