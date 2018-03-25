#ifndef FORMSYNCSHOP_H
#define FORMSYNCSHOP_H

#include <QDialog>

namespace Ui {
class formsyncshop;
}

class formsyncshop : public QDialog
{
    Q_OBJECT

public:
    explicit formsyncshop(QWidget *parent = 0);
    ~formsyncshop();

private:
    Ui::formsyncshop *ui;
};

#endif // FORMSYNCSHOP_H
