#include <QApplication>
#include "include/panels/welcomepanel.h"
#include "include/panels/customerpanel.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    std::unique_ptr<QMainWindow> window;

    WelcomePanel panel;
    panel.open();

    connect(&panel, &WelcomePanel::adminLoggedIn, this, [&](const Key &id)
        {

        }
    );
    connect(&panel, &WelcomePanel::customerLoggedIn, this, [&](const Key &id)
        {
            window = std::make_unique<CustomerPanel>(id);
            window->show();
        }
    );

    return app.exec();
}
