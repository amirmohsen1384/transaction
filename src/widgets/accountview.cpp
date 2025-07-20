#include "accountview.h"
#include "ui_accountview.h"

AccountView::AccountView(QWidget *parent) : QDialog(parent), ui(new Ui::AccountView)
{
    ui->setupUi(this);
    ui->primaryPasswordView->setReadOnly(true);
    ui->secondaryPasswordView->setReadOnly(true);
}

AccountView::~AccountView()
{
    delete ui;
}
