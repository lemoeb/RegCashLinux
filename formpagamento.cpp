#include "formpagamento.h"
#include "ui_formpagamento.h"

formpagamento::formpagamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formpagamento)
{
    ui->setupUi(this);

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
    emit(resetTable());
    //RegCashMain

}
