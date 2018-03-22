#ifndef FORMARTICOLI_H
#define FORMARTICOLI_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "azioni.h"
#include "errori.h"
#include "dbutility.h"

namespace Ui {
class formArticoli;
}

class formArticoli : public QDialog
{
    Q_OBJECT

private:
    void abilitaInserimento(void);
    void disabilitaInsMod(void);
    void abilitaModifica(void);
    void disabilitaCampiText(void);
    void resetForm(void);

public:
    explicit formArticoli(QWidget *parent = 0);
    ~formArticoli();

private slots:
    void on_btnAnnulla_clicked();
    void on_txtArticolo_returnPressed();
    void on_btnModifica_clicked();
    void on_txtArticolo_textChanged(const QString &arg1);
    void on_btnSalva_clicked();

private:
    Ui::formArticoli *ui;
    QSqlDatabase db = QSqlDatabase::database();
    dbUtility db2;
    int tipoSalvataggio =NO_ACTION;
};

#endif // FORMARTICOLI_H
