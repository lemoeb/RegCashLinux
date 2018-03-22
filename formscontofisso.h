#ifndef FORMSCONTOFISSO_H
#define FORMSCONTOFISSO_H

#include <QDialog>

namespace Ui {
class formscontofisso;
}

class formscontofisso : public QDialog
{
    Q_OBJECT

public:
    explicit formscontofisso(QWidget *parent = 0);
    ~formscontofisso();

private:
    Ui::formscontofisso *ui;

signals:
    void aggiornaScontoFisso(int);

private slots:
    void on_btnConferma_clicked();
};

#endif // FORMSCONTOFISSO_H
