#ifndef FORMREPORT_H
#define FORMREPORT_H

#include <QDialog>
#include <QDebug>

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
    void on_comboBox_currentIndexChanged(int index);


private:
    Ui::formreport *ui;
    void disabilitaCampiData(void);
    void abilitaCampiData(void);

};

#endif // FORMREPORT_H
