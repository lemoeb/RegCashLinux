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
    ui->setupUi(this);
    disabilitaCampiData();
    ui->lbl_wait->setVisible(false);
}

/**
 * @brief formreport::~formreport
 */
formreport::~formreport()
{
    delete ui;
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
}

/**
 * @brief formreport::generaReport
 */
void formreport::generaReport(){
    disabilitaCampiData();
    ui->cmbReport->setEnabled(false);
    ui->btnConferma->setEnabled(false);
    ui->btnAnnulla->setEnabled(false);
    ui->lbl_wait->setVisible(true);
}

/**
 * @brief formreport::on_comboBox_currentIndexChanged
 * @param index
 */
void formreport::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
        case 0: //Lista Articoli
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
