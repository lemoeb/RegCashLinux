#ifndef FORMREPORT_H
#define FORMREPORT_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "azioni.h"
#include "dbutility.h"
#include "messaggi.h"


namespace Ui {
class formreport;
}

class formreport : public QDialog
{
    Q_OBJECT

public:
    explicit formreport(QWidget *parent = 0);
    ~formreport();

private slots:

    void on_btnAnnulla_clicked();
    void on_btnConferma_clicked();

    void on_cmbReport_currentIndexChanged(int index);

private:
    Ui::formreport *ui;
    dbUtility db;
    QMessageBox messageBox;
    void disabilitaCampiData(void);
    void abilitaCampiData(void);
    void generaReport(void);
    void resetForm(void);

};

#endif // FORMREPORT_H
