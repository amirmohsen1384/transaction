#ifndef TRANSFERPANEL_H
#define TRANSFERPANEL_H

#include "include/core/cashtransaction.h"
#include "include/widgets/abstractpanel.h"

namespace Ui
{
    class TransferPanel;
}

class TransferPanel : public AbstractPanel
{
    Q_OBJECT
public:
    explicit TransferPanel(QWidget *parent = nullptr);
    ~TransferPanel();

public slots:
    void updateOwner(const QString &value);

    virtual void reset() override;
    virtual void reject() override;
    virtual void accept() override;

private:
    CashTransaction transaction;
    std::unique_ptr<Ui::TransferPanel> ui;
};

#endif // TRANSFERPANEL_H
