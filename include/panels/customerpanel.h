#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QMainWindow>
#include "include/models/customermodel.h"

namespace Ui {
class CustomerPanel;
}

class CustomerPanel : public QMainWindow
{
    Q_OBJECT
private slots:
    void updatePanel();
    void viewAccount(const QModelIndex &index);

public:
    explicit CustomerPanel(const Key &key, QWidget *parent = nullptr);
    ~CustomerPanel();

public slots:
    void transfer();
    void changePassword();

private:
    CustomerModel model;
    std::unique_ptr<Ui::CustomerPanel> ui;
};

#endif // CUSTOMERPANEL_H
