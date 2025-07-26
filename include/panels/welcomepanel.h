#ifndef WELCOMEPANEL_H
#define WELCOMEPANEL_H

#include <QDialog>
#include "include/general.h"

namespace Ui {
class WelcomePanel;
}

class WelcomePanel : public QDialog
{
    Q_OBJECT
private slots:
    void login();

public:
    explicit WelcomePanel(QWidget *parent = nullptr);
    ~WelcomePanel();

public slots:
    void createCustomer();

signals:
    void adminLoggedIn(const Key &id);
    void customerLoggedIn(const Key &id);

private:
    std::unique_ptr<Ui::WelcomePanel> ui;
};

#endif // WELCOMEPANEL_H
