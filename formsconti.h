#ifndef FORMSCONTI_H
#define FORMSCONTI_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "dbutility.h"


namespace Ui {
class formsconti;
}

class formsconti : public QDialog
{
    Q_OBJECT

public:
    explicit formsconti(QWidget *parent = 0);
    ~formsconti();

private slots:
    void on_btnConferma_clicked();

private:
    Ui::formsconti *ui;
    dbUtility db;

};

#endif // FORMSCONTI_H
