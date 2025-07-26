#include "welcomepanel.h"
#include "ui_welcomepanel.h"

WelcomePanel::WelcomePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WelcomePanel)
{
    ui->setupUi(this);
}

WelcomePanel::~WelcomePanel()
{
    delete ui;
}
