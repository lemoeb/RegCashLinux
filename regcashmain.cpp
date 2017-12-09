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

    //Definizione delle connessioni
    connect(ui->tbCassa,SIGNAL(backSpacePressed(float)),this,SLOT(test(float)));
    connect (frmPagamento,SIGNAL(chiudiScontrino(float)),this,SLOT(chiudiScontrino(float)));



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
            ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,2,new QTableWidgetItem(sconto+"%"));
            ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,3,new QTableWidgetItem(qry.value(2).toString()));

            //Calcolo dello valore scontato
            if (sconto!="0"){
                float scontoPerc=qry.value(2).toDouble() - (qry.value(2).toDouble() /100)*sconto.toInt();

                ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,4,new QTableWidgetItem(QString::number(scontoPerc) ));
            }
            else{
                ui->tbCassa->setItem   ( ui->tbCassa->rowCount()-1,4,new QTableWidgetItem(qry.value(2).toString()));
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
}


void RegCashMain::chiudiScontrino(float pagato){
    QString test = QString::number(pagato);
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
