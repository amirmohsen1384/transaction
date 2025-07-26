#include "include/panels/welcomepanel.h"
#include "include/dialogs/useredit.h"
#include "include/users/customer.h"
#include "include/users/admin.h"
#include "include/users/user.h"
#include "ui_welcomepanel.h"
#include <QMessageBox>
#include <QTimer>

void WelcomePanel::login()
{
    const auto &userName = ui->userNameEdit->text();
    const auto &password = ui->passwordEdit->password();
    const auto &admins = Storage::admin().entryInfoList
    (
        {QString("*.%1").arg(admin_suffix)},
        QDir::AllEntries | QDir::NoDotAndDotDot
    );
    qDebug() << "Fetched the list of admins...";
    qDebug() << admins;

    const auto &customers = Storage::customer().entryInfoList
    (
        {"*"},
        QDir::AllEntries | QDir::NoDotAndDotDot
    );
    qDebug() << "Fetched the list of customers...";
    qDebug() << customers;

    for(const auto &customer : customers)
    {
        auto id = customer.baseName().toLongLong();
        auto account = Customer::loadFromRecord(id);
        if(account.getUserName() == userName && account.getPassword() == password)
        {
            qDebug() << QString("%1 has been found with %2 and %3").arg(id).arg(userName).arg(password);
            emit customerLoggedIn(id);
            QDialog::accept();
            return;
        }
    }
    qDebug() << "No customer found with this user name and password.";

    for(const auto &admin : admins)
    {
        auto id = admin.baseName().toLongLong();
        auto account = Admin::loadFromRecord(id);
        if(account.getUserName() == userName && account.getPassword() == password)
        {
            qDebug() << QString("%1 has been found with %2 and %3").arg(id).arg(userName).arg(password);
            emit adminLoggedIn(id);
            QDialog::accept();
            return;
        }
    }
    qDebug() << "No admin found with this user name and password.";

    QMessageBox::critical(this, "Error", "You have entered an incorrect user name or password.");
}

WelcomePanel::WelcomePanel(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::WelcomePanel>();
    ui->setupUi(this);
    QTimer::singleShot(2000, [&]()
        {
            ui->pageContainer->setCurrentWidget(ui->loginPage);
        }
    );
}

WelcomePanel::~WelcomePanel() {}

void WelcomePanel::createCustomer()
{
    UserEdit editor(this);
    if(editor.exec() == QDialog::Accepted)
    {
        Customer customer;
        customer.setFirstName(editor.getFirstName());
        customer.setLastName(editor.getLastName());
        customer.setNationalCode(editor.getNationalCode());
        customer.setUserName(editor.getUserName());
        customer.setPassword(editor.getPassword());

        auto key = Customer::generateID();
        customer.saveToRecord(key);
    }
}
