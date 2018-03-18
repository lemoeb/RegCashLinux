#include "formreport.h"
#include "ui_formreport.h"

formreport::formreport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formreport)
{
    ui->setupUi(this);

}

formreport::~formreport()
{
    delete ui;
}

void formreport::disabilitaCampiData(){
  ui->ckData->setEnabled(false);
  ui->lblDataA->setEnabled(false);
  ui->lblDataA->setEnabled(false);
  ui->dateEditDa->setEnabled(false);
  ui->dateEditA->setEnabled(false);
}

void formreport::abilitaCampiData(){
  ui->ckData->setEnabled(true);
  ui->lblDataA->setEnabled(true);
  ui->lblDataA->setEnabled(true);
  ui->dateEditDa->setEnabled(true);
  ui->dateEditA->setEnabled(true);
}


void formreport::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
        case 0:
            disabilitaCampiData();
            break;
        case 1:
            abilitaCampiData();
            break;
        case 2:
            break;
        case 3:
            break;
    }
    qDebug() << "Selezionato indice " + QString::number(index);
}
