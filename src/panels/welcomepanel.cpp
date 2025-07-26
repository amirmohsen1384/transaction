#include "include/panels/welcomepanel.h"
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
    const auto &admins = Storage::admin().entryInfoList(
        {QString("*.%1").arg(admin_suffix)},
        QDir::AllEntries | QDir::NoDotAndDotDot,
    );
    const auto &customers = Storage::customer().entryInfoList(
        {QString("*.%1").arg(customer_suffix)},
        QDir::AllEntries | QDir::NoDotAndDotDot
    );
    for(const auto &customer : customers)
    {
        auto id = customer.baseName().toLongLong();
        auto account = Customer::loadFromRecord(id);
        if(account.getUserName() == userName && account.getPassword() == password)
        {
            emit customerLoggedIn(id);
            QDialog::accept();
            return;
        }
    }
    for(const auto &admin : admins)
    {
        auto id = admin.baseName().toLongLong();
        auto account = Admin::loadFromRecord(id);
        if(account.getUserName() == userName && account.getPassword() == password)
        {
            emit adminLoggedIn(id);
            QDialog::accept();
            return;
        }
    }
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
