#include "regcashmain.h"
#include "ui_regcashmain.h"
#include <QtSql>
#include <QMessageBox>
#include <QDebug>


RegCashMain::RegCashMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegCashMain)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint); //Set window with no title bar
    frmPagamento= new formpagamento;
    scontoFisso = new formscontofisso;
    QSqlQuery qry;

    //Impostazione dei pulsanti sconto
    qry=db.recuperaSconti();
    if (qry.next()){
        ui->btnSconto1->setText(ui->btnSconto1->text() + " " + qry.value(1).toString() + " %");

        while(qry.next()){
            switch(qry.value(0).toInt()){
                case 2:
                    ui->btnSconto2->setText(ui->btnSconto2->text() + " " + qry.value(1).toString() + " %");
                    break;
                case 3:
                    ui->btnSconto3->setText(ui->btnSconto3->text() + " " + qry.value(1).toString() + " %");
                    break;
                case 4:
                    ui->btnSconto4->setText(ui->btnSconto4->text() + " " + qry.value(1).toString() + " %");
                    break;
                case 5:
                    ui->btnSconto5->setText(ui->btnSconto5->text() + " " + qry.value(1).toString() + " %");
                    break;
            }
        }
    }
    else
    {
        QMessageBox::critical(this,"Errore","Impossibile recuperare gli sconti",QMessageBox::Ok);
        exit(1);

    }

    //Definizione delle connessioni
    connect (ui->tbCassa,SIGNAL(backSpacePressed(float)),this,SLOT(test(float)));
    connect (frmPagamento,SIGNAL(chiudiScontrino(float)),this,SLOT(chiudiScontrino(float)));
    connect (scontoFisso,SIGNAL(aggiornaScontoFisso(int)),this,SLOT(impostaScontoFisso(int)));


}

RegCashMain::~RegCashMain()
{
    delete ui;
}

void RegCashMain::test(float qqq){
    float Totale=ui->txtTotale->text().toFloat();
    Totale-=qqq;
    ui->txtTotale->setText((QString::number(Totale)));
    qInfo("Test signal");
}

/**
 * @brief RegCashMain::on_actionCassa_triggered
 */
void RegCashMain::on_actionCassa_triggered()
{
    qInfo( "Pulsante Cassa" );
}

/**
 * @brief RegCashMain::on_actionSconti_triggered
 */
void RegCashMain::on_actionSconti_triggered()
{
    sconti = new formsconti;
    sconti->exec();
}

/**
 * @brief RegCashMain::on_actionArticoli_triggered
 */
void RegCashMain::on_actionArticoli_triggered()
{
   pippo = new formArticoli;
   pippo->exec();
}

/**
 * @brief RegCashMain::on_actionExportData_triggered
 */
void RegCashMain::on_actionExportData_triggered()
{

}

/**
 * @brief RegCashMain::on_actionSyncShop_triggered
 */
void RegCashMain::on_actionSyncShop_triggered()
{

}

void RegCashMain::on_actionImpostazioni_triggered()
{
    frmImpostazioni = new formImpostazioni;
    frmImpostazioni->exec();
}


void RegCashMain::on_txtArticolo_returnPressed()
{
    QString par2Str = ui->txtArticolo->text();
    QString sconto = ui->txtSconto->text();
    float totale=ui->txtTotale->text().toDouble();
    sconto.remove('%');
    ui->txtArticolo->setText("");
    ui->txtDescArt->setText("");
    QSqlQuery qry;

    if (par2Str!=""){
        qry=db.ricercaArticolo(par2Str);
        if (qry.next()){
            ui->txtDescArt->setText("");
            ui->tbCassa->insertRow ( ui->tbCassa->rowCount());
            ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,0,new QTableWidgetItem(qry.value(0).toString()));
            ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,1,new QTableWidgetItem(qry.value(1).toString()));
            ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,2,new QTableWidgetItem(sconto+" %"));
            ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,3,new QTableWidgetItem(qry.value(2).toString()));

            //Calcolo dello valore scontato
            if (sconto!="0"){
                float scontoPerc=qry.value(2).toDouble() - (qry.value(2).toDouble() /100)*sconto.toInt();

                ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,4,new QTableWidgetItem(QString::number(scontoPerc) ));
            }
            else{
                ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,4,new QTableWidgetItem(qry.value(2).toString()));
            }


            if ((ui->txtSconto->text()!="") && (ui->txtSconto->text().toInt()!=0)){
                int sconto=ui->txtSconto->text().toInt();
                float totSconto=0;
                float prezzoIntero=0;
                float prezzoScontato=0;
                prezzoIntero=ui->tbCassa->item(ui->tbCassa->rowCount()-1,3)->text().toFloat();
                prezzoScontato=prezzoIntero-(prezzoIntero/100) * sconto;
                ui->tbCassa->setItem(ui->tbCassa->rowCount()-1,4,new QTableWidgetItem(QString::number(prezzoScontato)));
                ui->tbCassa->setItem(ui->tbCassa->rowCount()-1,2,new QTableWidgetItem(QString::number(sconto) + " %"));
                ui->tbCassa->item(ui->tbCassa->rowCount()-1,4)->setBackground(Qt::green);
                ui->tbCassa->item(ui->tbCassa->rowCount()-1,2)->setBackground(Qt::green);
            }

           totale+=ui->tbCassa->item(ui->tbCassa->rowCount()-1,4)->text().toFloat();
           ui->txtTotale->setText(QString::number(totale));
        }
        else{
             QMessageBox::critical(this,"Errore","Articolo non trovato",QMessageBox::Ok);
        }

      }

}

void RegCashMain::on_tbCassa_cellClicked(int row, int column)
{
   ui->tbCassa->selectRow(row);
}

void RegCashMain::on_btnContanti_clicked()
{
    frmPagamento->caricaDati(ui->txtTotale->text().toFloat(),PAGAMENTO_CONTANTI);
    frmPagamento -> exec();
}

void RegCashMain::resetCashTable(){
    ui->tbCassa->setRowCount(0);
    ui->txtTotale->setText("0");
}


void RegCashMain::chiudiScontrino(float pagato){
    QString test = QString::number(pagato);
    resetCashTable();
    qDebug() << test;
}

/**
 * @brief RegCashMain::on_btnAtm_clicked
 * @author  Leandro Materni
 * @version 1.0.0
 */
void RegCashMain::on_btnAtm_clicked()
{
    frmPagamento->caricaDati(ui->txtTotale->text().toFloat(),PAGAMENTO_ATM);
    frmPagamento -> exec();
}

/**
 * @brief RegCashMain::on_btnSconto1_clicked
 */
void RegCashMain::on_btnSconto1_clicked()
{
    int sconto=0;
    sconto=db.recuperaScontoSpecifico(1);
    applicaSconto(sconto);
}

/**
 * @brief RegCashMain::on_btnSconto2_clicked
 */
void RegCashMain::on_btnSconto2_clicked()
{
    int sconto=0;
    sconto=db.recuperaScontoSpecifico(2);
    applicaSconto(sconto);
}

/**
 * @brief RegCashMain::on_btnSconto3_clicked
 */
void RegCashMain::on_btnSconto3_clicked()
{
    int sconto=0;
    sconto=db.recuperaScontoSpecifico(3);
    applicaSconto(sconto);
}

/**
 * @brief RegCashMain::on_btnSconto4_clicked
 */
void RegCashMain::on_btnSconto4_clicked()
{
    int sconto=0;
    sconto=db.recuperaScontoSpecifico(4);
    applicaSconto(sconto);
}

/**
 * @brief RegCashMain::on_btnSconto5_clicked
 */
void RegCashMain::on_btnSconto5_clicked()
{
    int sconto=0;
    sconto=db.recuperaScontoSpecifico(5);
    applicaSconto(sconto);
}

/**
 * @brief applicaSconto
 * @param sconto
 */
void RegCashMain::applicaSconto(int sconto){
   int righeTabella=ui->tbCassa->rowCount();
   int i=0;
   float totale=0;
   for (i=0;i<righeTabella;i++){
       float totSconto=0;
       float prezzoIntero=0;
       float prezzoScontato=0;
       prezzoIntero=ui->tbCassa->item(i,3)->text().toFloat();
       prezzoScontato=prezzoIntero-(prezzoIntero/100) * sconto;
       ui->tbCassa->setItem(i,4,new QTableWidgetItem(QString::number(prezzoScontato)));
       ui->tbCassa->setItem(i,2,new QTableWidgetItem(QString::number(sconto) + " %"));
       ui->tbCassa->item(i,4)->setBackground(Qt::green);
       ui->tbCassa->item(i,2)->setBackground(Qt::green);
       totale+=prezzoScontato;
   }
   ui->txtTotale->setText(QString::number(totale));
}

void RegCashMain::on_btnScontoFisso_clicked()
{
    scontoFisso->exec();
}

/**
 * @brief RegCashMain::impostaScontoFisso
 * @param sconto
 */
void RegCashMain::impostaScontoFisso(int sconto){
    ui->txtSconto->setText(QString::number(sconto));
    if (sconto!=0){
        ui->txtSconto->setStyleSheet("QLineEdit { background-color: rgb(255, 139, 139);}");
    }
    else
    {
      ui->txtSconto->setStyleSheet("QLineEdit { background-color: rgb(255, 255, 255);}");
    }
}
