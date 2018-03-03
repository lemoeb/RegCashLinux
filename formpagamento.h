#ifndef FORMPAGAMENTO_H
#define FORMPAGAMENTO_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class formpagamento;
}

class formpagamento : public QDialog
{
    Q_OBJECT

public:
    explicit formpagamento(QWidget *parent = 0);
    void caricaDati(float,int);
    ~formpagamento();

private slots:
    void on_btnConferma_clicked();
    void on_btnAnnulla_clicked();
    //void visualizzaResto();

    void on_txtPagato_returnPressed();

private:
    Ui::formpagamento *ui;
    int tipoPagamento;

signals:
    void resetTable();
    void chiudiScontrino(float,int);

};

#endif // FORMPAGAMENTO_H
