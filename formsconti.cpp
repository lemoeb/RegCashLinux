#include "formsconti.h"
#include "ui_formsconti.h"
#include <QtSql>


formsconti::formsconti(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formsconti)
{
    ui->setupUi(this);
    QSqlQuery qry;
    qry=db.recuperaSconti();
    if (qry.next()){
        ui->sconto1->setText(qry.value(1).toString());

        while(qry.next()){
            switch(qry.value(0).toInt()){
                case 2:
                    ui->sconto2->setText(qry.value(1).toString());
                    break;
                case 3:
                    ui->sconto3->setText(qry.value(1).toString());
                    break;
                case 4:
                    ui->sconto4->setText(qry.value(1).toString());
                    break;
                case 5:
                    ui->sconto5->setText(qry.value(1).toString());
                    break;
            }
        }
    }
    else
    {
        QMessageBox::critical(this,"Errore","Impossibile receprare gli sconti",QMessageBox::Ok);
        this->close();

    }
}

formsconti::~formsconti()
{
    delete ui;
}

void formsconti::on_btnConferma_clicked()
{
    bool esito=false;
    int sconto1=ui->sconto1->text().toInt();
    int sconto2=ui->sconto2->text().toInt();
    int sconto3=ui->sconto3->text().toInt();
    int sconto4=ui->sconto4->text().toInt();
    int sconto5=ui->sconto5->text().toInt();

    esito=db.salvaSconti(sconto1,sconto2,sconto3,sconto4,sconto5);

    if (esito==true){
        QMessageBox::information(this,"Info","Sconti correttamente salvati",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(this,"Errore","Errore durante il salvataggio degli sconti",QMessageBox::Ok);
    }
}
