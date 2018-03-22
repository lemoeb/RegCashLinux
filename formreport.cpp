#include "formreport.h"
#include "ui_formreport.h"

/**
 * @brief formreport::formreport
 * @param parent
 */
formreport::formreport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formreport)
{
    QDate date = QDate::currentDate();
    ui->setupUi(this);
    disabilitaCampiData();
    ui->lbl_wait->setVisible(false);
    ui->dateEditA->setDate(date);
    ui->dateEditDa->setDate(date);
}

/**
 * @brief formreport::~formreport
 */
formreport::~formreport()
{
    delete ui;
}

void formreport::resetForm(){
    QDate date = QDate::currentDate();
    ui->cmbReport->setEnabled(true);
    ui->btnConferma->setEnabled(true);
    ui->btnAnnulla->setEnabled(true);
    ui->dateEditA->setDate(date);
    ui->dateEditDa->setDate(date);
}


/**
 * @brief formreport::disabilitaCampiData
 */
void formreport::disabilitaCampiData(){
  ui->ckData->setEnabled(false);
  ui->lblDataA->setEnabled(false);
  ui->lblDataA->setEnabled(false);
  ui->dateEditDa->setEnabled(false);
  ui->dateEditA->setEnabled(false);
}

/**
 * @brief formreport::abilitaCampiData
 */
void formreport::abilitaCampiData(){
  ui->ckData->setEnabled(true);
  ui->lblDataA->setEnabled(true);
  ui->lblDataA->setEnabled(true);
  ui->dateEditDa->setEnabled(true);
  ui->dateEditA->setEnabled(true);
  this->update();
}

/**
 * @brief formreport::generaReport
 */
void formreport::generaReport(){

    QSqlQuery qry;
    QString descErrore="";
    QString dataDa="";
    QString dataA="";
    int limiteRighe=0;
    QString limiteArticolo="";
    int numErrore=NO_ERROR;
    int filtraData=0;
    int filtraRighe=0;
    int filtraArticolo=0;

    int tipoReport=ui->cmbReport->currentIndex();
    disabilitaCampiData();
    ui->cmbReport->setEnabled(false);
    ui->btnConferma->setEnabled(false);
    ui->btnAnnulla->setEnabled(false);
    ui->lbl_wait->setVisible(true);
    filtraData=ui->ckData->checkState();
    filtraRighe=ui->ck_righe->checkState();
    filtraArticolo=ui->ck_articolo->checkState();
    this->update();
    QString tdateTime = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString outputFilename="";

    switch(tipoReport){
        case REPORT_LISTA_ARTICOLI:{

            outputFilename = "./report/listaArticoli_" + tdateTime + ".csv";
            QFile outputFileListaArticoli(outputFilename);
            outputFileListaArticoli.open(QIODevice::WriteOnly);
            if(!outputFileListaArticoli.isOpen()){
                messageBox.critical(this,ERROR_TITLE,REPORT_GENERATE_ERROR,messageBox.Ok);
            }
            else{

                qry=db.report(&descErrore,&numErrore,REPORT_LISTA_ARTICOLI,dataDa,dataA,limiteRighe,limiteArticolo,filtraData,filtraRighe,filtraArticolo);
                QTextStream outStream(&outputFileListaArticoli);
                QString riga ="";
                outStream << "Report;Lista Articoli" << endl << endl;
                riga="ARTICOLO;DESCRIZIONE;PREZZO;GIACENZA";
                outStream << riga << endl;

                while(qry.next()){
                    riga="";
                    riga += qry.value(0).toString() + ";" + qry.value(1).toString() + ";" + qry.value(2).toString() + ";" + qry.value(3).toString() + ";";
                    outStream << riga << endl;
                }
                outputFileListaArticoli.close();
                ui->lbl_wait->setVisible(false);
                messageBox.information(this,INFO_TITLE,REPORT_GENERATED,QMessageBox::Ok);
                resetForm();
            }

            this->update();
        }
        case REPORT_ARTICOLI_NO_GIACENZA:{

            outputFilename = "./report/listaArticoliNoGiacenza_" + tdateTime + ".csv";
            QFile outputFileNoGiacenza(outputFilename);
             outputFileNoGiacenza.open(QIODevice::WriteOnly);
            if(! outputFileNoGiacenza.isOpen()){
                messageBox.critical(this,ERROR_TITLE,REPORT_GENERATE_ERROR,messageBox.Ok);
            }
            else{

                qry=db.report(&descErrore,&numErrore,REPORT_ARTICOLI_NO_GIACENZA,dataDa,dataA,limiteRighe,limiteArticolo,filtraData,filtraRighe,filtraArticolo);
                QTextStream outStream(& outputFileNoGiacenza);
                QString riga ="";
                outStream << "Report;Lista Articoli" << endl << endl;
                riga="ARTICOLO;DESCRIZIONE;PREZZO;GIACENZA";
                outStream << riga << endl;

                while(qry.next()){
                    riga="";
                    riga += qry.value(0).toString() + ";" + qry.value(1).toString() + ";" + qry.value(2).toString() + ";" + qry.value(3).toString() + ";";
                    outStream << riga << endl;
                }
                 outputFileNoGiacenza.close();
                ui->lbl_wait->setVisible(false);
                messageBox.information(this,INFO_TITLE,REPORT_GENERATED,QMessageBox::Ok);
                resetForm();
            }

            this->update();
        }

    }


}


/**
 * @brief formreport::on_btnAnnulla_clicked
 */
void formreport::on_btnAnnulla_clicked()
{
    this->close();
}

/**
 * @brief formreport::on_btnConferma_clicked
 */
void formreport::on_btnConferma_clicked()
{
    generaReport();
}

void formreport::on_cmbReport_currentIndexChanged(int index)
{
    switch(index){
        case REPORT_LISTA_ARTICOLI: //Lista Articoli
            disabilitaCampiData();
            break;
        case 1: //Articoli senza Giacenza
            disabilitaCampiData();
            break;
        case 2: //Articoli Venduti
            abilitaCampiData();
            break;
        case 3: //Articoli più venduti
             abilitaCampiData();
            break;
        case 4: //Articoli che hanno generato più profitto
             abilitaCampiData();
            break;
    }
}
