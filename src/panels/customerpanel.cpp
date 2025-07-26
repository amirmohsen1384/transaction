#include "include/dialogs/accountpasswordeditor.h"
#include "include/dialogs/transferpanel.h"
#include "include/panels/customerpanel.h"
#include "include/dialogs/accountview.h"
#include "include/dialogs/useredit.h"
#include "ui_customerpanel.h"
#include <QMessageBox>

void CustomerPanel::updatePanel()
{
    ui->accountView->setVisible(model.rowCount() > 0);
    ui->transferButton->setVisible(model.rowCount() > 0);
    ui->noAccountLabel->setVisible(!(model.rowCount() > 0));
    connect(ui->accountView->selectionModel(), &QItemSelectionModel::currentChanged, this,
        [&](const QModelIndex &index)
        {
            ui->passwordEditButton->setVisible(index.isValid());
        }
    );
    const auto name = model.headerData(Qt::UserRole).value<Customer>().getName();
    ui->title->setText(QString("Welcome back, %1!").arg(name));
    setWindowTitle(QString("%1 - Customer Panel").arg(name));
}

void CustomerPanel::changeAccount()
{
    UserEdit editor(this);
    if(editor.exec() == QDialog::Accepted)
    {
        Customer data;
        data.setNationalCode(editor.getNationalCode());
        data.setFirstName(editor.getFirstName());
        data.setLastName(editor.getLastName());
        data.setUserName(editor.getUserName());
        data.setPassword(editor.getPassword());
        data.setAge(editor.getAge());

        model.setHeaderData(0, Qt::Horizontal, QVariant::fromValue(data), Qt::DisplayRole);
        updatePanel();
    }
}

void CustomerPanel::viewAccount(const QModelIndex &index)
{
    AccountView view(index.data(AbstractAccount::KeyRole).value<Key>());
    view.exec();
}

CustomerPanel::CustomerPanel(const Key &key, QWidget *parent) : QMainWindow(parent)
{
    ui = std::make_unique<Ui::CustomerPanel>();
    ui->setupUi(this);

    ui->accountView->setItemDelegate(new AccountDelegate(this));
    ui->passwordEditButton->setVisible(false);
    ui->accountView->setModel(&model);

    model.setIdentifier(key);
    updatePanel();
}

CustomerPanel::~CustomerPanel()
{}

void CustomerPanel::transfer()
{
    TransferPanel panel(this);
    panel.setModel(&model);
    panel.exec();
}

void CustomerPanel::changePassword()
{
    const auto &index = ui->accountView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    auto target = index.data(Qt::UserRole).value<std::shared_ptr<AbstractAccount>>();
    auto key = index.data(AbstractAccount::KeyRole).value<Key>();

    AccountPasswordEditor editor(this);
    editor.setPrimaryPassword(QString::number(target->getPrimaryPassword()));
    editor.setSecondaryPassword(QString::number(target->getSecondaryPassword()));
    if(editor.exec() == QDialog::Accepted)
    {
        target->setPrimaryPassword(editor.getPrimaryPassword().toInt());
        target->setSecondaryPassword(editor.getSecondaryPassword().toInt());
        target->saveToRecord(key);
        QMessageBox::information(this, "Successful", "Passwords have been changed successfully.");
    }
}
