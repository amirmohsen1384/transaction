#include "accountpasswordeditor.h"
#include "ui_accountpasswordeditor.h"

AccountPasswordEditor::AccountPasswordEditor(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::AccountPasswordEditor>();
    ui->setupUi(this);

    connect(ui->primaryPasswordEdit, &QLineEdit::textChanged, this, &AccountPasswordEditor::primaryPasswordChanged);
    connect(ui->secondaryPasswordEdit, &QLineEdit::textChanged, this, &AccountPasswordEditor::secondaryPasswordChanged);
}

AccountPasswordEditor::~AccountPasswordEditor() {}

QString AccountPasswordEditor::getPrimaryPassword() const
{
    return ui->primaryPasswordLineEdit->text();
}

QString AccountPasswordEditor::getSecondaryPassword() const
{
    return ui->secondaryPasswordLineEdit->text();
}

void AccountPasswordEditor::setPrimaryPassword(const QString &password)
{
    ui->primaryPasswordLineEdit->setText(password);
    emit primaryPasswordChanged(password);
}

void AccountPasswordEditor::setSecondaryPassword(const QString &password)
{
    ui->secondaryPasswordLineEdit->setText(password);
    emit secondaryPasswordChanged(password);
}