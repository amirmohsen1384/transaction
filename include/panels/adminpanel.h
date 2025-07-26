#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QMainWindow>
#include "include/general.h"

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdminPanel(const Key &value, QWidget *parent = nullptr);
    ~AdminPanel();

    Key getIdentifier() const;

public:
    void setIdentifier(const Key &value);

signals:
    void identifierChanged(const Key &value);

private:
    Key identifier;
    std::unique_ptr<Ui::AdminPanel> ui;
};

#endif // ADMINPANEL_H
