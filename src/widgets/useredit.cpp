#include "include/widgets/useredit.h"
#include "ui_useredit.h"

UserEdit::UserEdit(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::UserEdit>();
    ui->setupUi(this);
}

QString UserEdit::getFirstName() const
{
    return ui->firstNameEdit->text();
}

QString UserEdit::getLastName() const
{
    return ui->lastNameEdit->text();
}

QString UserEdit::getNationalCode() const
{
    return ui->nationalCodeEdit->text();
}

QString UserEdit::getUserName() const
{
    return ui->userNameEdit->text();
}

QString UserEdit::getPassword() const
{
    return ui->passwordEdit->password();
}

int UserEdit::getAge() const
{
    return ui->ageEdit->value();
}

void UserEdit::setFirstName(const QString &value)
{
    ui->firstNameEdit->setText(value);
    emit firstNameChanged(value);
}

void UserEdit::setLastName(const QString &value)
{
    ui->lastNameEdit->setText(value);
    emit lastNameChanged(value);
}

void UserEdit::setNationalCode(const QString &value)
{
    ui->nationalCodeEdit->setText(value);
    emit nationalCodeChanged(value);
}

void UserEdit::setUserName(const QString &value)
{
    ui->userNameEdit->setText(value);
    emit userNameChanged(value);
}

void UserEdit::setPassword(const QString &value)
{
    ui->passwordEdit->setPassword(value);
    emit passwordChanged(value);
}

void UserEdit::setAge(int value)
{
    ui->ageEdit->setValue(value);
    emit ageChanged(value);
}

UserEdit::~UserEdit()
{
}
