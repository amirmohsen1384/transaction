#include "include/widgets/transferpanel.h"
#include "ui_transferpanel.h"

TransferPanel::TransferPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransferPanel)
{
    ui->setupUi(this);
}

TransferPanel::~TransferPanel()
{
    delete ui;
}
