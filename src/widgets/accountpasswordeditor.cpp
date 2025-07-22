#include "include/widgets/accountpasswordeditor.h"
#include "ui_accountpasswordeditor.h"

AccountPasswordEditor::AccountPasswordEditor(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::AccountPasswordEditor>();
    ui->setupUi(this);

    connect(ui->primaryPasswordEdit, &PasswordEdit::passwordChanged, this, &AccountPasswordEditor::primaryPasswordChanged);
    connect(ui->secondaryPasswordEdit, &PasswordEdit::passwordChanged, this, &AccountPasswordEditor::secondaryPasswordChanged);
}

AccountPasswordEditor::~AccountPasswordEditor() {}

QString AccountPasswordEditor::getPrimaryPassword() const
{
    return ui->primaryPasswordEdit->password();
}

QString AccountPasswordEditor::getSecondaryPassword() const
{
    return ui->secondaryPasswordEdit->password();
}

void AccountPasswordEditor::setPrimaryPassword(const QString &password)
{
    ui->primaryPasswordEdit->setPassword(password);
    emit primaryPasswordChanged(password);
}

void AccountPasswordEditor::setSecondaryPassword(const QString &password)
{
    ui->secondaryPasswordEdit->setPassword(password);
    emit secondaryPasswordChanged(password);
}
