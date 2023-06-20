#include "mainwindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char **argv)
{
    //! [0]
    QApplication app(argc, argv);

    mainwindow *MainWindow = new mainwindow();

    return app.exec();
}
