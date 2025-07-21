#include "include/widgets/useredit.h"
#include "ui_useredit.h"

UserEdit::UserEdit(QWidget *parent) : QDialog(parent), ui(new Ui::UserEdit)
{
    ui->setupUi(this);
}

UserEdit::~UserEdit()
{
    delete ui;
}
