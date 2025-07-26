#include "include/panels/adminpanel.h"
#include "ui_adminpanel.h"

AdminPanel::AdminPanel(const Key &value, QWidget *parent) : QMainWindow(parent)
{
    ui = std::make_unique<Ui::AdminPanel>();
    ui->setupUi(this);

    setIdentifier(value);
}

AdminPanel::~AdminPanel() {}

Key AdminPanel::getIdentifier() const
{
    return identifier;
}

void AdminPanel::setIdentifier(const Key &value)
{
    identifier = value;
    emit identifierChanged(value);
}
