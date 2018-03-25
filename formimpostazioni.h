#ifndef FORMIMPOSTAZIONI_H
#define FORMIMPOSTAZIONI_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include "messaggi.h"


const int PRESTASHOP     = 1;
const int MAGENTO        = 2; //Not implemented in this Version
const int OS_COMMERCE    = 3; //Not implemented in this Version
const int SYNC_ACTIVE    = 2;
const int SYNC_DISACTIVE = 0;
const int DB_MYSQL       = 1;
const int DB_SQLITE      = 2;

namespace Ui {
class formImpostazioni;
}

class formImpostazioni : public QDialog
{
    Q_OBJECT

public:
    explicit formImpostazioni(QWidget *parent = 0);
    ~formImpostazioni();

private slots:
    void on_btnAnnulla_clicked();
    void on_btnConferma_clicked();
    void on_radio_sqlite_clicked();
    void on_radio_mysql_clicked();


private:
    Ui::formImpostazioni *ui;

};

#endif // FORMIMPOSTAZIONI_H
