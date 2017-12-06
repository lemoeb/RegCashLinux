#include "formimpostazioni.h"
#include "ui_formimpostazioni.h"

formImpostazioni::formImpostazioni(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formImpostazioni)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint); //Set window with no title bar
}

formImpostazioni::~formImpostazioni()
{
    delete ui;
}

void formImpostazioni::on_btnAnnulla_clicked()
{
    this->close();
}
