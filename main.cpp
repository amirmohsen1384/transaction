#include <QApplication>
#include "include/panels/welcomepanel.h"
#include "include/panels/customerpanel.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    std::unique_ptr<QMainWindow> window;

    WelcomePanel panel;
    panel.open();

    Customer cs = Customer::loadFromRecord(2133788);
    qDebug() << cs.getUserName();
    qDebug() << cs.getPassword();

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
