#ifndef FORMARTICOLI_H
#define FORMARTICOLI_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

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

public:
    explicit formArticoli(QWidget *parent = 0);
    ~formArticoli();

private slots:
    void on_btnAnnulla_clicked();
    void on_txtArticolo_returnPressed();

    void on_btnModifica_clicked();

private:
    Ui::formArticoli *ui;
    QSqlDatabase db = QSqlDatabase::database();
};

#endif // FORMARTICOLI_H
