#include <QApplication>
#include "include/panels/welcomepanel.h"
#include "include/panels/customerpanel.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    std::unique_ptr<QMainWindow> window;

    const auto &depositList = Storage::depositAccount().entryInfoList
    (
        {QString("*.%1").arg(deposit_suffix)},
        QDir::AllEntries | QDir::NoDotAndDotDot
    );
    for(const auto &account : depositList)
    {
        const auto id = account.baseName().toLongLong();
        auto data = DepositAccount::loadFromRecord(id);
        if(data.getLastCashMoved().addSecs(60 * 60 * 24) < QDateTime::currentDateTime())
        {
            data.setTransferredBalance(0);
            qDebug() << QString("Transferred balance of %1 with %2 has been reset.").arg(id).arg(data.getLastCashMoved().toString());
        }
        data.saveToRecord(id);
    }

    const auto &loanList = Storage::loanAccount().entryInfoList
    (
        {QString("*.%1").arg(loan_suffix)},
        QDir::AllEntries | QDir::NoDotAndDotDot
    );
    for(const auto &account : loanList)
    {
        const auto id = account.baseName().toLongLong();
        auto data = LoanAccount::loadFromRecord(id);
        if(data.getLastCashMoved().addSecs(60 * 60 * 24) < QDateTime::currentDateTime())
        {
            data.setTransferredBalance(0);
            qDebug() << QString("Transferred balance of %1 with %2 has been reset.").arg(id).arg(data.getLastCashMoved().toString());
        }
        data.saveToRecord(id);
    }

    const auto &transactionList = Storage::transactionAccount().entryInfoList
    (
        {QString("*.%1").arg(transaction_suffix)},
        QDir::AllEntries | QDir::NoDotAndDotDot
    );
    for(const auto &account : transactionList)
    {
        const auto id = account.baseName().toLongLong();
        auto data = TransactionAccount::loadFromRecord(id);
        if(data.getLastCashMoved().addSecs(60 * 60 * 24) < QDateTime::currentDateTime())
        {
            data.setTransferredBalance(0);
            qDebug() << QString("Transferred balance of %1 with %2 has been reset.").arg(id).arg(data.getLastCashMoved().toString());
        }
        data.saveToRecord(id);
    }

    WelcomePanel panel;
    panel.open();

    QObject::connect(&panel, &WelcomePanel::adminLoggedIn, [&](const Key &id)
        {

        }
    );
    QObject::connect(&panel, &WelcomePanel::customerLoggedIn, [&](const Key &id)
        {
            window = std::make_unique<CustomerPanel>(id);
            window->show();
        }
    );

    return app.exec();
}
