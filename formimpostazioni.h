#ifndef FORMIMPOSTAZIONI_H
#define FORMIMPOSTAZIONI_H

#include <QDialog>

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
