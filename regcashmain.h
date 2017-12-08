#ifndef REGCASHMAIN_H
#define REGCASHMAIN_H

#include <QMainWindow>
#include <QtSql>
#include "formarticoli.h"
#include "formimpostazioni.h"
#include "formpagamento.h"
#include "tipologiepagamento.h"
#include "dbutility.h"
#include "customtable.h"

namespace Ui {
class RegCashMain;
}

class RegCashMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegCashMain(QWidget *parent = 0);
    ~RegCashMain();


private slots:
    void on_actionCassa_triggered();

    void on_actionSconti_triggered();

    void on_actionArticoli_triggered();

    void on_actionExportData_triggered();

    void on_actionSyncShop_triggered();

    void on_txtArticolo_returnPressed();

    void on_tbCassa_cellClicked(int row, int column);

    void test(float qqq);

    //void pagamento (float totale,int tipoPagamento);

    void on_actionImpostazioni_triggered();

    void on_btnContanti_clicked();

    void on_btnAtm_clicked();

public slots:
    void resetCashTable();
    void chiudiScontrino(float);

private:
    Ui::RegCashMain *ui;
    QSqlDatabase db = QSqlDatabase::database();
    formArticoli *pippo;
    formImpostazioni *frmImpostazioni;
    formpagamento *frmPagamento;


};



#endif // REGCASHMAIN_H
