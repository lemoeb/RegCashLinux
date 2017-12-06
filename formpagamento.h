#ifndef FORMPAGAMENTO_H
#define FORMPAGAMENTO_H

#include <QDialog>
#include <QMainWindow>

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

private:
    Ui::formpagamento *ui;
    int tipoPagamento;

signals:
    void resetTable();

};

#endif // FORMPAGAMENTO_H
