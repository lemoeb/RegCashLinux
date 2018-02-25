#include "formpagamento.h"
#include "ui_formpagamento.h"
#include <QDebug>

formpagamento::formpagamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formpagamento)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint); //Set window with no title bar
    ui->txtEffettivo->setFocus();
}

formpagamento::~formpagamento()
{
    delete ui;
}

void formpagamento::caricaDati(float prezzo,int Pagamento)
{
    ui->txtTotale->setText(QString::number(prezzo));
    tipoPagamento=Pagamento;
}

void formpagamento::on_btnConferma_clicked()
{

    emit(chiudiScontrino(ui->txtEffettivo->text().toDouble(),tipoPagamento));
    ui->txtEffettivo->setText("");
    ui->txtPagato->setText("");
    ui->txtResto->setText("");
    ui->txtTotale->setText("");
    this->close();
}

void formpagamento::on_btnAnnulla_clicked()
{
     this->close();
}

void formpagamento::on_txtPagato_returnPressed()
{
    float totale=ui->txtTotale->text().toDouble();
    float effettivo = 0;
    float pagato = 0;
    float resto = 0;
    if (ui->txtEffettivo->text()!=""){
       effettivo=ui->txtEffettivo->text().toDouble();
    }

    if (ui->txtPagato->text()!="."){
        pagato=ui->txtPagato->text().toDouble();
        QString messaggio="";
        messaggio=ui->txtPagato->text();
        qDebug() << messaggio;
    }
    else{
        QMessageBox::critical(this,"Errore","E' necessario specificare il Pagato",QMessageBox::Ok);
        ui->txtPagato->setFocus();
    }

    if (effettivo!=0){
        resto=effettivo-pagato;
    }
    else
    {
        resto=totale-pagato;
    }
    ui->txtResto->setText(QString::number(resto));
    ui->btnConferma->setFocus();

}
