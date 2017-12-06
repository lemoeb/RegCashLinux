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
