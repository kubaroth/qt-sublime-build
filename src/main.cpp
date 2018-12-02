#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(simpletreemodel);

    QApplication app(argc, argv);
    auto mainwindow = new MainWindow();
    mainwindow->show();
    return app.exec();
}
