#ifndef TRANSFERPANEL_H
#define TRANSFERPANEL_H

#include <QWidget>

namespace Ui {
class TransferPanel;
}

class TransferPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TransferPanel(QWidget *parent = nullptr);
    ~TransferPanel();

private:
    Ui::TransferPanel *ui;
};

#endif // TRANSFERPANEL_H
