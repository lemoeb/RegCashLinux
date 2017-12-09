#ifndef FORMSCONTI_H
#define FORMSCONTI_H

#include <QDialog>

namespace Ui {
class formsconti;
}

class formsconti : public QDialog
{
    Q_OBJECT

public:
    explicit formsconti(QWidget *parent = 0);
    ~formsconti();

private:
    Ui::formsconti *ui;
};

#endif // FORMSCONTI_H
