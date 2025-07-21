#include "include/widgets/passwordeditor.h"
#include "ui_passwordeditor.h"

PasswordEditor::PasswordEditor(QWidget *parent) : QWidget(parent), ui(new Ui::PasswordEditor)
{
    ui->setupUi(this);
}

PasswordEditor::~PasswordEditor()
{
    delete ui;
}
