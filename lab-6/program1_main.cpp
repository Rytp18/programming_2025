#include <QApplication>
#include "program1window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("helmet creator");

    Program1Window window;
    window.show();

    return app.exec();
}