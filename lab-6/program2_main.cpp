#include <QApplication>
#include "program2window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("helmet viewer");

    Program2Window window;
    window.show();

    return app.exec();
}