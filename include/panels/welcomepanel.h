#ifndef WELCOMEPANEL_H
#define WELCOMEPANEL_H

#include <QMainWindow>

namespace Ui {
class WelcomePanel;
}

class WelcomePanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit WelcomePanel(QWidget *parent = nullptr);
    ~WelcomePanel();

private:
    Ui::WelcomePanel *ui;
};

#endif // WELCOMEPANEL_H
