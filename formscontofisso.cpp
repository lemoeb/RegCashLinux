#include "formscontofisso.h"
#include "ui_formscontofisso.h"

formscontofisso::formscontofisso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formscontofisso)
{
    ui->setupUi(this);
}

formscontofisso::~formscontofisso()
{
    delete ui;
}

void formscontofisso::on_btnConferma_clicked()
{
    emit(aggiornaScontoFisso(ui->txtScontoFisso->text().toInt()));
    ui->txtScontoFisso->setText("");
    this->close();

}
