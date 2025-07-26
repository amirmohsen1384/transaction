#include "include/panels/adminpanel.h"
#include "ui_adminpanel.h"

AdminPanel::AdminPanel(QWidget *parent) : QMainWindow(parent)
{
    ui = std::make_unique<Ui::AdminPanel>();
    ui->setupUi(this);
}

AdminPanel::~AdminPanel() {}
