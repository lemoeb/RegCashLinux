#include "formsconti.h"
#include "ui_formsconti.h"

formsconti::formsconti(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formsconti)
{
    ui->setupUi(this);
}

formsconti::~formsconti()
{
    delete ui;
}
