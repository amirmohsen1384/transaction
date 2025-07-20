#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QMainWindow>

namespace Ui {
class CustomerPanel;
}

class CustomerPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerPanel(QWidget *parent = nullptr);
    ~CustomerPanel();

private:
    Ui::CustomerPanel *ui;
};

#endif // CUSTOMERPANEL_H
