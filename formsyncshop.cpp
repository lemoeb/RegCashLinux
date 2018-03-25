#include "formsyncshop.h"
#include "ui_formsyncshop.h"

formsyncshop::formsyncshop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formsyncshop)
{
    ui->setupUi(this);
}

formsyncshop::~formsyncshop()
{
    delete ui;
}
