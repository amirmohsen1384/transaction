#include "include/panels/customerpanel.h"
#include "ui_customerpanel.h"

CustomerPanel::CustomerPanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomerPanel)
{
    ui->setupUi(this);
}

CustomerPanel::~CustomerPanel()
{
    delete ui;
}
